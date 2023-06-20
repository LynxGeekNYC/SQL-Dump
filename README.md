# SQL-Dump
SQL Dump for MyDQL and MariaDB detector and monitor. This script checks the MySQL/MariaDB error log file (/var/log/mysql/error.log in this example) for any occurrence of the string "mysqldump". If it finds a line containing this string, it assumes that a SQL data dump is in progress and raises an alert or takes appropriate action.
