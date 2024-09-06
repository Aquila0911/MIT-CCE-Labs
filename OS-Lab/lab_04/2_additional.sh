#!/bin/bash

# Check if the user provided input years
if [ $# -ne 2 ]; then
    echo "Usage: $0 <start_year> <end_year>"
    exit 1
fi

start_year=$1
end_year=$2

# Check if the input years are valid
if ! [[ "$start_year" =~ ^[0-9]{4}$ && "$end_year" =~ ^[0-9]{4}$ ]]; then
    echo "Invalid input years format. Please provide years in YYYY format."
    exit 1
fi

# Check if the start year is before the end year
if [ $start_year -gt $end_year ]; then
    echo "Start year cannot be greater than end year."
    exit 1
fi

# Calculate the range for find command
start_date="${start_year}-01-01 00:00:00"
end_date="${end_year}-12-31 23:59:59"

# Use find command to display files created between the input years range
find . -type f -newermt "$start_date" ! -newermt "$end_date"
