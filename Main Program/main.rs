use std::fs::File;
use std::io::{self, BufRead, BufReader};
use std::path::Path;
use aes::{Aes128, cipher::{BlockDecrypt, KeyInit}};
use base64::engine::{Engine};
use cipher::generic_array::GenericArray;

fn main() {
    println!("Enter the path to the encrypted file: ");
    let mut file_path = String::new();
    io::stdin().read_line(&mut file_path).expect("Error reading file path");
    let file_path = file_path.trim(); // Remove newline character

    let file = File::open(Path::new(file_path)).expect("Error opening file");
    let reader = BufReader::new(file);

    let mut base64_encoded_message = String::new();
    for line in reader.lines() {
        base64_encoded_message.push_str(&line.expect("Error reading line from file"));
    }

    // Decode the base64-encoded encrypted file content
    let decoded = base64::decode(&base64_encoded_message).expect("Failed to decode base64");

    // Key converted to ascii "ThisPasswordBad!" 
    let key = b"ThisPasswordBad!";

    // Setup AES decryption with KeyInit 
    let cipher = Aes128::new_from_slice(key).expect("Failed to create cipher");

    let mut decrypted_message = Vec::new();

    // Decrypt the base64-decoded message
    for chunk in decoded.chunks(16) {
        let mut block = GenericArray::clone_from_slice(chunk);
        cipher.decrypt_block(&mut block);
        decrypted_message.extend_from_slice(&block);
    }

    // Print the decrypted message
    println!("Decrypted message: {}", String::from_utf8_lossy(&decrypted_message));
}
