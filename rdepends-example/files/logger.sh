#!/bin/sh

# ==============================
# Real-Time System Monitor
# ==============================

while true
do
    clear
    echo "======================================"
    echo "        SYSTEM MONITOR (LIVE)"
    echo "======================================"
    echo "Date: $(date)"
    echo

    echo "----- CPU LOAD -----"
    uptime
    echo

    echo "----- MEMORY USAGE -----"
    free -h
    echo

    echo "----- DISK USAGE -----"
    df -h /
    echo

    echo "----- TOP PROCESSES -----"
    ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -10
    echo

    sleep 5
done