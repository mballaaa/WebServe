# Program to generate a random number between 0 and 9

# importing the random module
import random

def generate_random_text(length=random.randint(100,999999)):
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    random_text = ''.join(random.choice(alphabet) for _ in range(length))
    return random_text

if __name__ == "__main__":
    random_text = generate_random_text()
    print(random_text)

