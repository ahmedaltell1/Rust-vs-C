
use sha2::{Digest, Sha256};
use std::fs::File;
use std::io::{self, Read, Write};
use std::path::PathBuf;

fn main() -> io::Result<()> {
    let mut input = String::new();

    // Prompts user for file path and reads it
    println!("Enter the path to the file:");
    io::stdin().read_line(&mut input)?;
    let file_path = PathBuf::from(input.trim_end());
    input.clear(); // Clears input for next use

    // enter expected hash
    println!("Enter the expected hash digest of the file contents:");
    io::stdin().read_line(&mut input)?;
    let expected_hash = input.trim_end().to_lowercase(); // Normalize expected hash to lowercase

    // Opens file at given path and read its contents
    let mut file = File::open(file_path)?;
    let mut contents = Vec::new();
    file.read_to_end(&mut contents)?;

    // Calculates the hash of the files contents
    let hash = Sha256::digest(&contents); 
    let calculated_hash = format!("{:x}", hash); // hash as a hexadecimal string

    // Print the calculated hash 
    println!("Calculated hash digest: {}", calculated_hash);

    // Compares calculated hash with expected hash
    if calculated_hash == expected_hash {
        println!("Success: The calculated hash matches the expected hash.");
    } else {
        println!("Failure: The calculated hash does not match the expected hash.");
    }

    Ok(())
}
