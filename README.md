# Concurrent Banking Transaction Engine

This project is a Concurrent Banking Transaction Engine implemented in C as part of the CSP / CEP laboratory.

It is a multi-client TCP server that allows multiple users to perform banking operations concurrently while ensuring correctness, consistency, thread safety, and crash recovery.

---

## Problem Statement

Design and implement a banking server that supports concurrent client requests such as deposits, withdrawals, balance inquiries, and money transfers while preventing race conditions, deadlocks, and data loss during crashes.

---

## Features

- Multi-client TCP server
- Thread pool using POSIX threads
- Per-account mutex locking
- Deadlock-free transfer operations
- Write-Ahead Logging (WAL)
- Crash recovery using WAL replay

---

## CSP Topics Covered

- Multithreading
- Synchronization using mutexes and condition variables
- Concurrency control
- Deadlock prevention
- TCP socket programming
- File handling
- Durability and crash recovery

---



