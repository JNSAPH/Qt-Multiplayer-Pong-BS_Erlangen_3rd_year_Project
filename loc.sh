#!/bin/bash

# Suche alle .cpp und .h Dateien in diesem Verzeichnis und allen 
Unterverzeichnissen
FILES=$(find . -type f \( -name "*.cpp" -o -name "*.h" \))

# Initialisiere Variablen
TOTAL_LINES=0
FILE_COUNT=0

# Schleife durch jede Datei
for file in $FILES; do
    # Zähle die Anzahl der Zeilen in der aktuellen Datei
    lines=$(wc -l < "$file")

    # Füge die Anzahl der Zeilen dieser Datei zur Gesamtanzahl hinzu
    TOTAL_LINES=$((TOTAL_LINES + lines))

    # Inkrementiere den Dateizähler
    FILE_COUNT=$((FILE_COUNT + 1))

    # Gib die Anzahl der Zeilen für diese Datei aus
    echo "$file: $lines"
done

# Gib die Gesamtanzahl der Zeilen und die Anzahl der Dateien aus
echo "Total lines: $TOTAL_LINES"
echo "Files counted: $FILE_COUNT"

