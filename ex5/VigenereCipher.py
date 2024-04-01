class VigenereCipher:
    ALPHA_BET_BIG = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    ALPHA_BET_SMALL = 'abcdefghijklmnopqrstuvwxyz'
    ENCRYPTE_SIGN = 1
    DECRYPTE_SIGN = -1
    
    def __init__(self, keys):
        self.keys = keys
    
    def encrypt_char_by_k(self, char, k):
        if char.isalpha():
            is_upper = char.isupper()
            alphabet = self.ALPHA_BET_BIG if is_upper else self.ALPHA_BET_SMALL
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
        return self.encrypt_by_keys(decrypted, self.k, self.ENCRYPTE_SIGN)

    def decrypt(self, encrypted):
        return self.encrypt_by_keys(encrypted, self.k, self.DECRYPTE_SIGN)
    
    