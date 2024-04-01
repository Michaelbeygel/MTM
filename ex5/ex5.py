import json
import os

ALPHA_BET_BIG = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
ALPHA_BET_SMALL = 'abcdefghijklmnopqrstuvwxyz'
ENCRYPTE_SIGN = 1
DECRYPTE_SIGN = -1

class CaesarCipher:

    def __init__(self, k):
        self.k = k

    def encrypt_char_by_k(self, char, k):
        if char.isalpha():
            is_upper = char.isupper()
            alphabet = ALPHA_BET_BIG if is_upper else ALPHA_BET_SMALL
            shifted_index = (alphabet.index(char) + k) % len(alphabet)
            encrypted_char = alphabet[shifted_index]
        else: 
            encrypted_char = char
        
        return encrypted_char

    def encrypt_by_k(self, decrypted, k, sign): 
        encrypted = ""
        for char in decrypted:
            encrypted += self.encrypt_char_by_k(char, sign*k)
            
        return encrypted

    def encrypt(self, decrypted): 
        return self.encrypt_by_k(decrypted, self.k, ENCRYPTE_SIGN)

    def decrypt(self, encrypted):
        return self.encrypt_by_k(encrypted, self.k, DECRYPTE_SIGN)
    
    def shift_key(self, delta):
        self.k += delta
        
class VigenereCipher:
    
    def __init__(self, keys):
        self.keys = keys
    
    def encrypt_char_by_k(self, char, k):
        if char.isalpha():
            is_upper = char.isupper()
            alphabet = ALPHA_BET_BIG if is_upper else ALPHA_BET_SMALL
            shifted_index = (alphabet.index(char) + k) % len(alphabet)
            encrypted_char = alphabet[shifted_index]
        else: 
            encrypted_char = char

        return encrypted_char
    
    def encrypt_by_keys(self, decrypted, keys, sign): 
        encrypted = ""
        index = 0
        for char in decrypted:
            encrypted += self.encrypt_char_by_k(char, sign*keys[index])
            if char.isalpha():
                index = (index + 1) % len(self.keys)

        return encrypted

    def encrypt(self, decrypted): 
        return self.encrypt_by_keys(decrypted, self.keys, ENCRYPTE_SIGN)

    def decrypt(self, encrypted):
        return self.encrypt_by_keys(encrypted, self.keys, DECRYPTE_SIGN)
    
    

def loadEncryptionSystem(dir_path, plaintext_suffix):
    # Read myfile.json
    with open(os.path.join(dir_path, 'config.json'), 'r') as f:
       loaded_dict = json.load(f)

    encryptionSystem = CaesarCipher(loaded_dict['key']) if loaded_dict['type'] == 'Caesar' else VigenereCipher(loaded_dict['key']) 
    
    toEncrypt = loaded_dict['encrypt']
    
    suffix = plaintext_suffix if toEncrypt else 'enc'
    new_suffix = 'enc' if toEncrypt else plaintext_suffix
    
    for filename in os.listdir(dir_path):
        if filename.endswith(suffix):
            file_path = os.path.join(dir_path, filename)
            with open(file_path, 'r') as file:
                massage = file.read()
            new_file_path = os.path.join(dir_path, os.path.splitext(filename)[0] + new_suffix)
            with open(new_file_path, 'w') as new_file:
                new_massage = encryptionSystem.encrypt(massage) if toEncrypt else encryptionSystem.decrypt(massage)
                new_file.write(new_massage)

