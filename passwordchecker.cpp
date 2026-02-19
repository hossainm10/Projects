#include <iostream>
#include <string>
#include <cctype>

using std::cin, std::string, std::cout, std::endl;

bool validation(string password){
	bool is_digit= false;
	bool is_upper=false;
	bool is_alphanum=true;

	if(password.size() < 8){
		return false;
	}
	else{
		for(char c : password){
			if(std::isdigit(c))
				is_digit=true;
			if(std::isupper(c))
				is_upper=true;
			if(!(std::isalnum(c)))
				is_alphanum=false;
		}
	}
	
	return is_digit && is_upper && !(is_alphanum);

}


int main(){
	while(true){
		string password;
		cout<<"Enter a password: ";
		cin>>password;
		if(password=="q"){
			cout<<"Leaving password checker \nBreaking!"<<endl;
			break;
		}
		if(validation(password)){
			cout<<"Valid Password!"<<endl;
		}
		else{
			cout<<"Invalid Password"<<endl;
		}
	}
	return 0;

}
