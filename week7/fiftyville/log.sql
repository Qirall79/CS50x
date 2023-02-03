-- Keep a log of any SQL queries you execute as you solve the mystery.

--getting the description of the theft
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";

-- description
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

--Getting the interviews related to the theft
SELECT id, transcript FROM interviews WHERE transcript LIKE "%the courthouse%" AND year = 2020 AND month = 7 AND day = 28;

/* transcript
161 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
      If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

162 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse,
      I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

163 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
      In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

-- Getting the license plate of people who quit the courthouse parking within 10 minutes after the theft
SELECT license_plate FROM courthouse_security_logs WHERE activity = "exit" AND year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

--Creating a table to store the id of the suspecious people
CREATE TABLE sus (id INTEGER, name TEXT, phone_number TEXT, passport_number TEXT);

--Inserting infos of the sus people to the table
INSERT INTO sus (id, name, phone_number, passport_number) SELECT id, name, phone_number, passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE activity = "exit" AND year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);

--Deleting all the people who didn't withdraw that day from the fifer street of atm from sus table
DELETE FROM sus WHERE id NOT IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));

--Deleting people who didn't call in that same day less than 60 seconds
DELETE FROM sus WHERE phone_number NOT IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);

--Getting the nearest flight that were done with those sus people left in the table
SELECT * FROM flights WHERE id IN (SELECT flight_id FROM passengers WHERE passport_number IN (SELECT passport_number FROM sus)) AND year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute;
-- flight id = 36

-- Filtering the guy who took that flight from the sus
DELETE FROM sus WHERE passport_number NOT IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

--getting the accomplice
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM sus WHERE name = "Ernest") AND duration < 60 AND year = 2020 AND month = 7 AND day = 28);

--getting the city to which he escaped
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);