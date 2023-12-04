#!/bin/bash

cleanup() {
    echo "Cleaning up..."
    
    pkill -f "dotnet run"
    
    pkill -f "npm run serve"
    
    echo "Processes terminated."
    exit 0
}

trap cleanup SIGINT

if systemctl is-active --quiet postgresql; then
    echo "postgres service is running"
else
    sudo systemctl start postgresql

    if [ $? -eq 0 ]; then
        echo "postgres service is now running"
    else
        echo "Failed to start psql"
        cleanup
    fi
fi

cd SmartHouse.API
dotnet run &
echo "Backend launched..."

cd ../SmartHouse.Client.Web
npm run serve &
echo "Frontend launched..."

wait
