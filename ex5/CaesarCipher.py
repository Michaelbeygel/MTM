class CaesarCipher:
    ALPHA_BET_BIG = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    ALPHA_BET_SMALL = 'abcdefghijklmnopqrstuvwxyz'
    ENCRYPTE_SIGN = 1
    DECRYPTE_SIGN = -1

    def __init__(self, k):
        self.k = k

    def encrypt_char_by_k(self, char, k):
        if char.isalpha():
            is_upper = char.isupper()
            alphabet = self.ALPHA_BET_BIG if is_upper else self.ALPHA_BET_SMALL
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
        return self.encrypt_by_k(decrypted, self.k, self.ENCRYPTE_SIGN)

    def decrypt(self, encrypted):
        return self.encrypt_by_k(encrypted, self.k, self.DECRYPTE_SIGN)
    
    def shift_key(self, delta):
        self.k += delta
        
        
        