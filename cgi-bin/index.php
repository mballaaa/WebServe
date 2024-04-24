<?php

// Function to count the number of lines entered
function countLines() {
    $lineCount = 0;
    
    // Read input from stdin until EOF (End Of File) is reached
    while (($line = fgets(STDIN)) !== false) {
        // Increment line count for each line read
        $lineCount++;
    }
    
    return $lineCount;
}

// Call the function to count lines and store the result
$lines = countLines();

// Output the result
echo "Number of lines entered: $lines\n";

?>