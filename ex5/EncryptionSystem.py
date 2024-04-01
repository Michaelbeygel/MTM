import json
import os
import CaesarCipher
import VigenereCipher

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


loadEncryptionSystem("mt