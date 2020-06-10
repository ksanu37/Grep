#include <bits/stdc++.h>
using namespace std;

bool getPattern(string str, string s) 
{ 
    bool flag = false; 
    for (int i = 0; i < str.length(); i++) { 
        if ((str.substr(i, s.length()) == s) ) { 
        	if(str[i+s.length()]==' ' || str[i+s.length()]=='.'){
            	return true; 
            }
        } 
    } 
    return false;
}

bool getOccurance(string line, string pattern){
    for (int i = 0; i < line.length(); i++) { 
        if (line.substr(i, pattern.length()) == pattern) { 
            return true;
        } 
    } 
    return false;
}


bool ignoreCase(string line, string pattern){
	string tempLine = line;
	string tempPattern = pattern;		
	transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower); 
	transform(tempPattern.begin(), tempPattern.end(), tempPattern.begin(), ::tolower); 
	return getOccurance(tempLine, tempPattern);
}

string convertToString(char* a, int size) 
{ 
    int i; 
    string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

int main(int argc, char* argv[]){
	string pattern;
	char* filename;
	vector<char>options(4,0);
	/*
	if(argc==4){
		pattern = convertToString(argv[2], sizeof(argv[2]) / sizeof(char));
		filename = argv[3];
		options.clear();
	}
	
	else{
		filename = argv[4];
		pattern =  convertToString(argv[3], sizeof(argv[2]) / sizeof(char));
		for(int i=0; argv[2][i]!='\0'; i++){
			if(argv[2][i]!='-' && argv[2][i]!=' '){
				switch(argv[2][i]){
				    case 'i': options[0] = 1;
	   						break;
	   				case 'v': options[1] = 1;
	   					break;
	   				case 'w' : options[2] = 1;
	   					break;
	   				case 'n' : options[3] = 1;
	   					break;	
				}
			}
		}
	}
   	*/
    
   cout<<"If you want to implement the default behaviour of grep (Without Options), Please enter Y, else enter N\n";

   char userInput;
   cin>>userInput;

   string fileInput;
   string input[4];

   if(userInput == 'Y' || userInput== 'y'){
   	cout<<"Enter the command\n";

   	for(int i=0; i<3; i++){
   		cin>>input[i];
   	}

   	pattern = input[1];
   	fileInput = input[2];
   	options.clear();
   }
   
   else if(userInput=='N' || userInput=='n'){
	   cout<<"Enter grep option pattern filename\n";
	   	
	   for(int i=0; i<4; i++){
	   	cin>>input[i];
	   } 
	   
	   fileInput = input[3];
	   pattern = input[2];   /* Find out the pattern to be searched */
	}
	
	else{
	    cout<<"Please enter a valid input\n";
	    return 0;
	}

   fstream file;
   vector<string>result;
   int count = 0;
   
   for(int i=0; i<input[1].length(); i++){       /* getting all the options */
   		if(input[1][i]!='-' && input[1][i]!=' '){
   			switch(input[1][i]){
   				case 'i': options[0] = 1;
   						break;
   				case 'v': options[1] = 1;
   					break;
   				case 'w' : options[2] = 1;
   					break;
   				case 'n' : options[3] = 1;
   					break;
			   }
		   }
   }
   file.open(fileInput.c_str(),ios::in); 
   if (file.is_open()){   //checking whether the file is open
      string line;
      while(getline(file, line)){ //read data from file object and put it into string.
	         count++;
	         
	         if(options.size()==0){
			     if(getOccurance(line, pattern))
	         	 	result.push_back(line);
	         	}
	         			
	         else{
	         	string temp = line;
	         	bool check = true;
	         	
	         	if(options[0]==1){
				 	transform(line.begin(), line.end(), line.begin(), ::tolower); 
					//transform(tempPattern.begin(), tempPattern.end(), tempPattern.begin(), ::tolower); 
	         		check  = check & ignoreCase(line,pattern);
	         	}
	         	
	         	if(options[1]==1)
	         		check = check & !getOccurance(line,pattern);
	         	
	         	if(options[2]==1)
	         		check = check & getPattern(line, pattern);
	         		
	            if(options[3]==1)
	         	    temp = to_string(count)+": "+ temp;

				 
                 if(check)
				 		result.push_back(temp);
			}

		} 
    }
     
    for(int i=0; i<result.size(); i++)
      	cout<<result[i]<<"\n";
      	
    file.close(); //close the file object.
}
