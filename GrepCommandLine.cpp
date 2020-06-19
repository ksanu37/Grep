#include <bits/stdc++.h>
using namespace std;

/* A method to check whether the exact match to the pattern exists in the line or not */
bool getPattern(string str, string s) { 
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

/* A method to check if the pattern is a substring of the line or not */
bool getOccurance(string line, string pattern){
    for (int i = 0; i < line.length(); i++) { 
        if (line.substr(i, pattern.length()) == pattern) { 
            return true;
        } 
    } 
    return false;
}

/* A method to check for the existence of the pattern in the line, irrespective of the lettercase, line is passed in lowercase letters, here 
pattern is transformed to lowercase letters and getOccurance is simply called */
bool ignoreCase(string line, string pattern){
	string tempLine = line;
	string tempPattern = pattern;		
	transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower); 
	transform(tempPattern.begin(), tempPattern.end(), tempPattern.begin(), ::tolower); 
	return getOccurance(tempLine, tempPattern);
}

/* An utility function to convert a character array to C++ style string */
string convertToString(char* a, int size) { 

    int i; 
    string s = ""; 
    for (i = 0; a[i]!='\0'; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

int main(int argc, char* argv[]){
	
	if(argc<4 || argc>5){       // Expected arguments are  ./main grep line sample.txt  or ./main grep -i line sample.txt   format: location of the object file grep options pattern and filename 
		cout<<"INVALID COMMAND\n";
		return 0;
	}	
	string pattern;
	char* filename;
	int optionCount = 0;    
	vector<char>options(4,0);      /* Options are stored in a binary vector as i, v, w, n */
	if(argc==4){
		pattern = convertToString(argv[2], sizeof(argv[2]) / sizeof(char));
		filename = argv[3];
		options.clear();     // Resize the options vector in case the options are not provided by the user
		optionCount = 0;
	}
	
	else{
		filename = argv[4];
		pattern =  convertToString(argv[3], sizeof(argv[3]) / sizeof(char));
		if(argv[2][0]!='-'){
			cout<<"INVALID COMMAND, Please put a hyphen before the options\n";
			return 0;
		}
		for(int i=0; argv[2][i]!='\0'; i++){
			if(argv[2][i]!='-' && argv[2][i]!=' '){
				switch(argv[2][i]){   /* A Switch-case for setting up options for execution */
				    case 'i': options[0] = 1;
				    			optionCount++;
	   						break;
	   				case 'v': options[1] = 1;
	   							optionCount++;
	   					break;
	   				case 'w' : options[2] = 1;
	   							optionCount++;
	   					break;
	   				case 'n' : options[3] = 1;
	   							optionCount++;
	   					break;	
				}
			}
		}
	}

   fstream file;
   vector<string>result;
   int count = 0;
   file.open(filename,ios::in); 
   
   if (file.is_open()){   //checking whether the file is open
      string line;
      while(getline(file, line)){ //read data from file object and put it into string.
	         count++;     /* Counting the line number */
	         if(options.size()==0){
			     if(getOccurance(line, pattern))
	         	 	result.push_back(line);
	         	}
	         			
	         else{
	         	string temp = line;
	         	bool check = true;  /* A boolean variable to handle multiple options at the same time, if it ends up being true, 
	         						   the line is added to the result vector, else it is not added to the result vector */
	         	
	         	if(options[0]==1){   /* Case -i */
				 	transform(line.begin(), line.end(), line.begin(), ::tolower); 
	         		check  = check & ignoreCase(line,pattern);
	         	}
	         	
	         	if(options[1]==1)  /* Case -v */
	         		check = check & !getOccurance(line,pattern);
	         	
	         	if(options[2]==1) /* Case -w */
	         		check = check & getPattern(line, pattern);
	         		
	           if(options[3]==1){  /* Case -n */
	           	     stringstream ss;  
					  ss<<count;  
					  string s;  
					  ss>>s;
					  if((optionCount==1 && getOccurance(line, pattern)) || optionCount>1 )
	         			temp = s+": "+ temp;
	         		  else
	         		  		check = false;
	         	}

				 
                 if(check)
				 		result.push_back(temp);
			}

		} 
    }
    
    else{
    	cout<<"File Not Found\n";
    	return 0;
	}
    
    cout<<"###### RESULT #######\n";
    // Print the result 
    for(int i=0; i<result.size(); i++)
      	cout<<result[i]<<"\n";
      	
    file.close(); //close the file object.
}
