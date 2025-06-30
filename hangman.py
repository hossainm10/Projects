import random
from hangmanwords import word_list
from hangmandrawing import draw_stage



to_guess= random.choice(word_list)
print(to_guess)

placeholder=''

correct_letters=[]
for i in to_guess:
    placeholder+="_"


game_over=False
MAX_LIVES=7
strikes=0

print('Welcome to hangman--PYTHON VERSION--/n')
print("You get 7 strikes. You gain a strike for every incorrect letter.")
while not game_over:
    letter_guessed = input("Guess a letter: ").lower()
    display_word = ''
    if letter_guessed in correct_letters:
        print("You already guessed this letter. No strikes though")
    
    for i in to_guess:
        if letter_guessed==i:
            print("Letter correct")
            display_word+=i
            correct_letters.append(letter_guessed)
        elif i in correct_letters:
            display_word+=i
            print("You're already guessed this letter")
            
        else:
            print("Letter Wrong")
            display_word+="-"
        
    print(display_word)
    if letter_guessed not in to_guess:
        strikes+=1
        print(f"The letter you guessed, {letter_guessed} is not in the word. You gained strike. Strike count{strikes}")
        if strikes == MAX_LIVES:
            game_over=True
            print('you lose')
    if '-' not in display_word:
        game_over=True
        print(f'You WIN! You got every letter right')
        print(f"The word was {to_guess}")
    draw_stage(strikes)