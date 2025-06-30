alphabet=["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
numbers=["1","2","3","4","5","6","7","8","9","0"]
order=input("Enter 'encode' to Encrypt or 'decode' to Decrypt: \n").lower()
message=input("Enter the message you want to send: \n").lower()
shift=int(input("Enter the shift number: \n"))


def encrypt(org_text,amount):
    new_message=''
  
    for i in org_text:
        if i not in alphabet:
            if i in numbers:
                new_num=numbers[(numbers.index(i)+amount) % len(numbers)]
                new_message+=new_num
            else:
                new_message+=i
        else:
            new_letter=alphabet[(alphabet.index(i)+amount)% len(alphabet)] 
            new_message+=new_letter

    print(f'Here is the encoded message: {new_message}')

def decrypt(org_text,amount):
    decrypted=''
    amount*=-1
    for i in org_text:
        if i not in alphabet:
            if i in numbers:
                new_num=numbers[(numbers.index(i)+amount) % len(numbers)]
                decrypted+=new_num
            else:
                decrypted+=i
        else:
            new_letter=alphabet[(alphabet.index(i)+amount)% len(alphabet)] 
            decrypted+=new_letter
    print(f'Here is the decoded message: {decrypted}')

def caesar(org_text,amount,enc_or_dec):
    if enc_or_dec=="encode":
        encrypt(org_text,amount)
    if enc_or_dec=='decode':
        decrypt(org_text,amount)

caesar(message,shift,order)

should_cont=True
while should_cont:
    play_again=input(("Would like to decode or encode again? Type yes or no: \n" )).lower()
    if play_again=="yes":
        new_order= input((" You've selected yes. Would you like to encode or decode? \n "))
        new_msg=input('Type the new message: \n').lower()
        shift=int(input("Enter how many shifts: \n"))
        caesar(new_msg,shift,new_order)
    else:
        print("You have selected no, so this program will quit, thanks for playing! ")
        should_cont=False

    