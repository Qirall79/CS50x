import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = db.execute("SELECT * FROM owns WHERE user_id = ?", session["user_id"])

    user_portfolio = []

    user_cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    total_cash = user_cash

    for row in user:

        stock = row["stock"]
        quantity = row["quantity"]
        current_price = lookup(stock)["price"]
        stock_total = current_price * float(quantity)

        user_portfolio.append({"stock": stock, "quantity": quantity, "price": current_price, "total": stock_total})

    for element in user_portfolio:
        total_cash += element["total"]


    return render_template("index.html", portfolio = user_portfolio, cash = user_cash, total = total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        stock_name = request.form.get("symbol")
        amount = request.form.get("shares")
        user_id = session["user_id"]

        for i in amount:
            if not i.isdigit():
                return apology("Amount must be a number")
        amount = int(amount)

        if amount <= 0:
            return apology("Amount must be positive")

        if not stock_name:
            return apology("Stock name required")
        if not amount:
            return apology("The amount is required")
        if not lookup(stock_name):
            return apology("Invalid Symbol")

        current_price= lookup(stock_name)["price"]

        user_cash = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]["cash"]

        required_amount = current_price * float(amount)

        if user_cash < required_amount:
            return apology("Your cash isn't enough to buy that amount of shares")


        #updating the cash for the user after buying
        current_cash = user_cash - required_amount

        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, user_id)

        date = datetime.now().strftime("%d/%m/%Y %H:%M:%S")

        # making sure if that user has already that stock, if so we will update the quantity of shares for that stock
        result = db.execute("SELECT * FROM owns WHERE user_id = ? AND stock = ?", user_id, stock_name)

        if len(result) == 1:
            current_quantity = int(result[0]["quantity"]) + int(amount)

            db.execute("UPDATE owns SET quantity = ? WHERE user_id = ? AND stock = ?", current_quantity, user_id, stock_name)

        #if he doesn't have that stock, we gonna add a row for his id, the name of the stock and the shares he bought
        else:
            db.execute("INSERT INTO owns (user_id, stock, quantity) VALUES (?, ?, ?)", user_id, stock_name, amount)

        db.execute("INSERT INTO history (user_id, stock, quantity, type, date) VALUES (?, ?, ?, ?, ?)", user_id, stock_name, amount, "Buy", date)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    transactions = db.execute("SELECT * FROM history WHERE user_id = ? ORDER BY id DESC", user_id)

    return render_template("history.html", transactions = transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        symbol = request.form.get("symbol")

        stock = lookup(symbol)

        if not stock:
            return apology("Invalid symbol")

        return render_template("quoted.html", stock = stock)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Username required")
        if not password:
            return apology("Password required")
        if not confirmation:
            return apology("Password confirmation required")
        if password != confirmation:
            return apology("Passwords don't match")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) >= 1:
            return apology("Username already exists")

        hash_password = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_password)

        return redirect("/login")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        stock = request.form.get("symbol")
        amount = request.form.get("shares")
        user_id = session["user_id"]

        if not stock:
            return apology("Stock name required")

        if not lookup(stock):
            return apology("Invalid symbol")

        if not amount:
            return apology("The amount is required")

        amount = int(amount)

        if amount <= 0:
            return apology("The amount must be positive and not null")

        #checking if he owns the stock
        check = db.execute("SELECT * FROM owns WHERE stock = ? AND user_id = ?", stock, user_id)

        if len(check) < 1:
            return apology("You don't own this stock")

        #checking if he owns that amount shares
        if check[0]["quantity"] < amount:
            return apology("You don't own that much shares of this stock")

        if check[0]["quantity"] == amount:
            db.execute("DELETE FROM owns WHERE stock = ? AND user_id = ?", stock, user_id)

        else:
            new_quantity = check[0]["quantity"] - amount

            db.execute("UPDATE owns SET quantity = ? WHERE stock = ? AND user_id = ?", new_quantity,stock, user_id)

        income = float(amount) * lookup(stock)["price"]
        cash = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]["cash"]

        new_cash = cash + income

        date = datetime.now().strftime("%d/%m/%Y %H:%M:%S")

        db.execute("INSERT INTO history (user_id, stock, quantity, type, date) VALUES (?, ?, ?, ?, ?)", user_id, stock, amount, "Sell", date)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        return redirect("/")


    else:

        stocks = db.execute("SELECT * FROM owns WHERE user_id = ?", session["user_id"])

        shares = []

        for s in stocks:
            shares.append(s["stock"])

        return render_template("sell.html", shares = shares)



@app.route("/settings")
@login_required
def settings():
    return render_template("settings.html")

@app.route("/passwordchange", methods=["POST", "GET"])
@login_required
def password_change():

    if request.method == "POST":
        password = request.form.get("password")
        new = request.form.get("new")
        confirm = request.form.get("confirm")

        old = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["hash"]

        if not check_password_hash(old, password):
            return apology("Password Incorrect")

        if not confirm:
            return apology("Confirmation is required")

        if not password:
            return apology("Current password is required")

        if not new:
            return apology("New Password is required")


        if new != confirm:
            return apology("Passwords don't match")

        new_hash = generate_password_hash(new)

        if check_password_hash(old, new):
            return apology("Don't use the previous password")

        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash, session["user_id"])

        return redirect("/")


    else:
        return render_template("password.html")


@app.route("/addcash", methods=["POST", "GET"])
@login_required
def add_cash():

    if request.method == "POST":

        amount = int(request.form.get("amount"))
        new_cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"] + amount

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])

        date = datetime.now().strftime("%d/%m/%Y %H:%M:%S")

        db.execute("INSERT INTO history (user_id, stock, quantity, type, date) VALUES (?, ?, ?, ?, ?)", session["user_id"], "USDT", amount, "Add", date)

        return redirect("/")

    else:
        return render_template("cash.html")

@app.route("/delete")
@login_required
def delete():
        return render_template("delete.html")

@app.route("/deleteregret", methods=["POST"])
@login_required
def regret():
        return redirect("/")


@app.route("/deleteaccept", methods=["POST"])
@login_required
def accept():

        db.execute("DELETE FROM owns WHERE user_id = ?", session["user_id"])
        db.execute("DELETE FROM history WHERE user_id = ?", session["user_id"])
        db.execute("DELETE FROM users WHERE id = ?", session["user_id"])

        return redirect("/logout")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
