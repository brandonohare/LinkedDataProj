
#include "storm.h"

/*
    The following block is the main function
*/
int main(int argc, char *argv[])
{

    int inputNum = std::stoi(argv[1]);  //Getting the number of years
    std::ifstream myFile;               //Input file stream variable (details)
    std::ifstream myFile2;              //Input file stream varable (fatalities)
    int i = 0;                          //Loop var
    int hashSize = 0;                   //Hash size variable
    
    /*
        The following block counts the number of lines in all inputted files
    */
    int* yearsLength = new int[inputNum];
    while(i < inputNum)                                     //While loop to count lines for all input files
    {
        std::string fileYear = argv[2+i];                   //Getting the years, one by one, after the number is specified
        std::string file = "details-" + fileYear + ".csv";  //Taking that year and creating the correct filename
        myFile.open(file);                                  //Opening the file for that year
        hashSize = hashSize + getNumLines(myFile);          //Increasing hashSize variable by the file size
        myFile.close();                                     //Closing the file for that year
        myFile.open(file);
        yearsLength[i] = getNumLines(myFile);
        myFile.close();
        i++;                                                //Iterate though the files
    } 



    /*
        The following block instantiates the hashTable, and initializes each index to NULL
    */
    int hashTableS = hashTableSize(hashSize);                           //Using a function to find the hash table size
    hash_table_entry** hashTable = new hash_table_entry*[hashTableS];   //Instantiating the hash table of pointers to structures
    for(int k = 0; k < hashTableS; k++)
    {
        hashTable[k] = NULL;                                            //Initializing the hash table with null values
    }
    

    /*
        The following loop handles the instantiation and initialization to the entire data structure,
        for the storm events, the annual events, and the fatality events
    */
    annual_storms* yearArr = new annual_storms[inputNum];       //Instantiating array of annual_storms objects
    i = 0;                                                      //Loop var
    while(i < inputNum)                                         //Iterating through each year to put all information in data structures
    {
        /*
            The following block accesses the file names from the command line
        */
        std::string fileYear = argv[2+i];                       //Getting the years, one by one, after the number is specified
        std::string file = "details-" + fileYear + ".csv";      //Taking that year and creating the correct filename (details)
        std::string file2 = "fatalities-" + fileYear + ".csv";  //Taking that year and creating the correct filename (fatalities)
        std::string useless;                                    //Creating var for useless file line


        /*
            The following block fills a fatality event array for the given year in the loop
        */
        myFile2.open(file2);                                            //Opening fatalities for the current year to get number of lines
        int numLinesFat = getNumLines(myFile2);                         //Getting the number of lines
        myFile2.close();                                                //Closing the file
        fatality_event* fatalArr = new fatality_event[numLinesFat];     //Instantiating array of fatality events
        myFile2.open(file2);
        std::getline(myFile2, useless);                                 // Iterating past the first line of CSV file
        for(int h = 0; h < numLinesFat; h++)
        {
            
            std::string f_id;
            std::getline(myFile2, f_id, ',');                           //Getting the fatality id and adding it to the storm event
            fatalArr[h].fatality_id = std::stoi(f_id);
            
            std::string e_id;
            std::getline(myFile2, e_id, ',');                           //Getting the event id and adding it to the storm event
            fatalArr[h].event_id = std::stoi(e_id);
            
            std::string f_ty;
            std::getline(myFile2, f_ty, ',');                           //Getting the fatality type and adding it to the storm event
            fatalArr[h].fatality_type = f_ty[0];
            
            std::string f_da;
            std::getline(myFile2, f_da, ',');                           //Getting the fatality date and adding it to the storm event
            strcpy(fatalArr[h].fatality_date, f_da.c_str());
            
            std::string f_a;
            std::getline(myFile2, f_a, ',');                            //Getting the fatality age and adding it to the storm event
            if(f_a == "")
            {
                fatalArr[h].fatality_age = 0;
            }
            if(f_a != "")
            {
                fatalArr[h].fatality_age = std::stoi(f_a);
            }
            
            
            std::string f_s;
            std::getline(myFile2, f_s, ',');                            //Getting the fatality sex and adding it to the storm event
            if(f_s == "")
            {
                fatalArr[h].fatality_sex = 0;
            }
            if(f_s != "")
            {
                fatalArr[h].fatality_sex = f_s[0];
            }
            
            std::string f_l;
            std::getline(myFile2, f_l);                                 //Getting the fatality location and adding it to the storm event
            strcpy(fatalArr[h].fatality_location, f_l.c_str());

            fatalArr[h].next = NULL;
        }
        myFile2.close();

        
        /*
            The following block fills in all the data from the csv files per year and fills a storm array
        */
        int fileYearInt = std::stoi(fileYear);                      //Turning the file year into an int 
        myFile.open(file);                                          //Opening the file for that year
        yearArr[i].year = fileYearInt;                              //Setting annual_storms with the year
        int numLinesDet = getNumLines(myFile);                      //Getting the number of lines for just one file
        //std::cout << "Number of Lines in Details: " << numLinesDet << "\n";
        myFile.close();                                             //Closing the file to re-use getlines
        storm_event* eventArr = new storm_event[numLinesDet];   //Instantiating storm_event array for the current file
        myFile.open(file);                                          //Opening the new file
        std::getline(myFile, useless);                              // Iterating past the first line of CSV file
        for(int j = 0; j < numLinesDet; j ++)                   //Adding event information line by line into the index (j)
        {
            
            std::string e_id;
            std::getline(myFile, e_id, ',');                    //Getting the event id and adding it to the storm event
            eventArr[j].event_id = std::stoi(e_id);
            //std::cout << "Event Id: " << eventArr[j].event_id << "\n";

            
            std::string s;
            std::getline(myFile, s, ',');                       //Getting the state and adding it to the storm event
            strcpy(eventArr[j].state, s.c_str());

            
            std::string y;
            std::getline(myFile, y, ',');                       //Getting the year and adding it to the storm event
            eventArr[j].year = std::stoi(y);

            
            std::string m;
            std::getline(myFile, m, ',');                       //Getting the month name and adding it to the storm event
            strcpy(eventArr[j].month_name, m.c_str());

            
            std::string e_ty;
            std::getline(myFile, e_ty, ',');                    //Getting the event type and adding it to the storm event
            strcpy(eventArr[j].event_type, e_ty.c_str());

            
            std::string cz_t;
            std::getline(myFile, cz_t, ',');                    //Getting the cz type and adding it to the storm event
            eventArr[j].cz_type = cz_t[0];

            
            std::string cz_n;
            std::getline(myFile, cz_n, ',');                    //Getting the cz name and adding it to the storm event
            strcpy(eventArr[j].cz_name, cz_n.c_str());

            
            std::string i_d;
            std::getline(myFile, i_d, ',');                     //Getting the injuries direct and adding it to the storm event
            eventArr[j].injuries_direct = std::stoi(i_d);

            
            std::string i_in;
            std::getline(myFile, i_in, ',');                    //Getting the injuries indirect and adding it to the storm event
            eventArr[j].injuries_indirect = std::stoi(i_in);

    
            std::string d_d;
            std::getline(myFile, d_d, ',');                     //Getting the death direct and adding it to the storm event
            eventArr[j].deaths_direct = std::stoi(d_d);

            std::string d_in;
            std::getline(myFile, d_in, ',');                    //Getting the deaths indirect and adding it to the storm event
            eventArr[j].deaths_indirect = std::stoi(d_in);
            
            
            std::string d_p;
            std::getline(myFile, d_p, ',');                     //Getting the damage to property and adding it to the storm event
            char mult = d_p[d_p.length() - 1];                  //Finding the multiplier (Thousands or Millions)
            if(d_p[0] == '.')                                   //Checking for a period and removing it to perform stoi
            {
                int size = d_p.length();
                d_p = d_p.substr(1, size-1);
            }
            int num = std::stoi(d_p);
            if(mult == 'K')                                     //Thousands
            {
                num = num * 1000;
            }
            if(mult == 'M')                                     //Millions
            {
                num = num * 1000000;
            }
            eventArr[j].damage_property = num;                  //Setting


            std::string d_c;
            std::getline(myFile, d_c, ',');                     //Getting the damage to crops and adding it to the storm event
            char mult1 = d_c[d_c.length() - 1];                 //Finding the multiplier (Thousands or Millions)
            if(d_c[0] == '.')                                   //Checking for a period and removing it to perform stoi
            {
                int size = d_c.length();
                d_c = d_c.substr(1, size-1);
            }
            int num1 = std::stoi(d_c);
            if(mult1 == 'K')                                    //Thousands
            {
                num1 = num1 * 1000;
            }
            if(mult1 == 'M')                                    //Millions
            {
                num1 = num1 * 1000000;
            }
            eventArr[j].damage_crops = num1;
            

            
            std::string t_f_s;                                  
            std::getline(myFile, t_f_s);                        //Getting the tor f scale
            strcpy(eventArr[j].tor_f_scale, t_f_s.c_str());

            eventArr[j].f = NULL;                               //Initialiing fatality events to NULL
            

            /*
                The following block handles linking fatality events to the proper storm event
            */
            for(int t = 0; t < numLinesFat; t++)                    //Looping as many times are there are fatality events
            {
                if(fatalArr[t].event_id == eventArr[j].event_id)    //If the event IDs match
                {
                    if(eventArr[j].f == NULL)
                    {
                        eventArr[j].f = &fatalArr[t];
                    }
                    else
                    {
                        if(eventArr[j].f->next == NULL)
                        {
                            eventArr[j].f->next = &fatalArr[t];
                        }
                        else
                        {
                            fatality_event* temp = eventArr[j].f->next;
                            while(temp->next != NULL)
                            {
                                temp = temp->next;
                            }
                            if(temp->next == NULL)
                            {
                                temp->next = &fatalArr[t];
                            }

                        }
                        
                    }
                    
                    /*
                    if(fatalArr[t].next != NULL)                    //If there is a linked list already in plane
                    {
                        fatality_event newNode;
                        fatality_event head;
                        head = fatalArr[t]; 
                        newNode = fatalArr[t];
                        newNode.next = &head;
                        fatalArr[t] = newNode;
                    }
                    else                                            //If there is no linked list
                    {
                        eventArr[j].f = &fatalArr[t];
                    }
                    */
                }
            }
            
            /*
                The following block handles filling the hash table with data and
                implementing separate chaining
            */
            int function = hashFunction(eventArr[j].event_id, hashSize);     //Running hash function
            if(hashTable[function] == NULL)                                     //If there is nothing in the index create event info
            {
                hash_table_entry* entry = new hash_table_entry;                 
                hashTable[function] = entry;
                hashTable[function]->event_id = eventArr[j].event_id;
                hashTable[function]->year = eventArr[j].year;
                hashTable[function]->event_index = j;
                hashTable[function]->next = NULL;
            }
            if(hashTable[function] != NULL)                                     //If there is already an entry, implement chaining
            {
                hash_table_entry* newEntry = new hash_table_entry;
                hash_table_entry* head = new hash_table_entry;
                head = hashTable[function];
                newEntry->event_id = eventArr[j].event_id;
                newEntry->year = eventArr[j].year;
                newEntry->event_index = j; 
                newEntry->next = head;
                hashTable[function] = newEntry; 
            }
        }
        yearArr[i].events = eventArr;   //Add this year's events to annual storms array
        myFile.close();
        i++;                            //Incrementing
    }
    

    /*
        The following block is a rudimentary handling of queries
    */
    std::cout << "Input Number of Queries: ";
    std::string numQuer;
    std::cin >> numQuer;                                                        //Setting the number of queries to be handled
    std::cout << "Menu:\nfind event (event number)\nfind max (#) (year/all) (damage_type)\nfind max fatality (#) (year/all)\nrange (year/all) (state/month) (low) (high)\nsummary\n";
    int numQ = std::stoi(numQuer);                                              //Turning that into an integer
    std::string query;
    std::string word;
    std::cout << "";
    for(int i = 0; i < numQ; i++)
    {
        if(i == 0)
        {
            std::cin.ignore();                 
            std::getline(std::cin, query);
        }
        else
        {
           std::getline(std::cin, query);
        }
        std::istringstream str(query);
        str >> word;

        if(word == "find")                                                     //If statement for find event query
        {
            str >> word;
            if(word == "event")
            {
                str >> word;
                int event = std::stoi(word);
                findEvent(hashTable, yearArr, event, hashTableS, inputNum, hashSize);         //Finding the event
            }

            if(word == "max")
            {
                str >> word;
                if(word == "fatality")                                      //If statement for max fatality
                {
                    str >> word; 
                    int number = std::stoi(word);
                    str >> word;
                    std::string year = word;
                    findMaxFatality(number, year, yearsLength, yearArr, inputNum, "fatality");
                }
                else
                {
                    int number = std::stoi(word);
                    str >> word;
                    std::string year = word;
                    str >> word;
                    std::string type = word;
                    findMax(number, year, yearsLength, yearArr, inputNum, type);
                }   
            }  
        }
        if(word == "range")
        {
            str >> word;
            std::string year = word;
            str >> word;
            std::string field = word;
            str >> word;
            std::string low = word;
            str >> word;
            std::string high = word;
            range(year, field, low, high, yearsLength, inputNum, yearArr);

        }
        if(word == "summary")                                      //If statement for the summary
        {
            summary(hashTable, hashTableS);
        }
        str.clear();
    }
    summary(hashTable, hashTableS);
    return 0;   //END OF MAIN
}


/*
    The following function gets the number of lines in a file (assuming it has already been opened)
*/
int getNumLines(std::ifstream &file)
{
    int i = 0;
    std::string whoCares = "";
    while(std::getline(file, whoCares))
    {
        i++;
    }
    return i - 1;
}


/*
    The following functions sets the hash table size to 2*size->next closest prime
*/
int hashTableSize(int size)
{
    int value = size * 2;
    while(!TestForPrime(value))
    {
        value++;
    }
    return value;
}

/*
    The following function outputs the index in the hash table via the hash function
*/
int hashFunction(int eventId, int tableSize)
{
    int value = floor(eventId%tableSize);
    return value;
}


/*
    The following function was given by professor Syrotiuk, returns T || F based on whether a value is prime
*/
bool TestForPrime(int val)
{
    int limit, factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return( factor > limit );
}

/*
    The following function searches the data structure for an inputted event id and prints the details
*/
void findEvent(hash_table_entry** arr, annual_storms* arr2, int event_i, int hashS, int numYears, int lines)
{
    
    int location = hashFunction(event_i, lines);
    if(arr[location] == NULL)
    {std::cout << "Does not exist" << "\n";}

    if(arr[location] != NULL && arr[location]->event_id == event_i)
    {
        for(int i = 0; i < numYears; i++)
        {
            if(arr2[i].year == arr[location]->year)
            {
                printDetails(arr2, i, arr[location]->event_index);
            }
        }
    }

    if((arr[location] != NULL) && (arr[location]->event_id != event_i) && (arr[location]->next != NULL))
    {
        
        hash_table_entry* temp = arr[location]->next;
        while(temp->event_id != event_i)
        {
            if(temp->next != NULL)
            {temp = temp->next;}
            if(temp->next == NULL)
            {std::cout << "Does not exist" << "\n";}
        } 
        if(temp->event_id == event_i)
        {
            for(int i = 0; i < numYears; i++)
            {
                if(arr2[i].year == temp->year)
                {
                    printDetails(arr2, i, temp->event_index);
                }
            }
        }
    }
}


/*
    The following function prints out each index and how long each chain is
*/
void summary(hash_table_entry** hashT, int hashS)
{
    double keysUsed = 0;
    for(int l = 0; l < hashS-1; l++)
    {
        int count = 0;
        int spread = 0;
        if(hashT[l]!= NULL)
        {
            keysUsed++;
            std::cout << "Index " << l << " ";
            if(hashT[l]->next != NULL)
            {
                count++;
                spread++;
                hash_table_entry* temp = hashT[l]->next;
                while(temp->next != NULL)
                {
                    count++;
                    
                    temp = temp->next;
                }
                
            }
            std::cout << count << "\n";  
        }  
    }
    double loadFactor = (keysUsed/hashS);
    std::cout << "Load Factor: " << (loadFactor*100) << "%" <<  std::endl;

}

/*
    The following function prints all the details for a storm event
*/
void printDetails(annual_storms* arr2, int arrI, int eventI)
{
    std::cout << arr2[arrI].events[eventI].event_id << "\n";
    std::cout << arr2[arrI].events[eventI].state << "\n";
    std::cout << arr2[arrI].events[eventI].year << "\n";
    std::cout << arr2[arrI].events[eventI].month_name<< "\n";
    std::cout << arr2[arrI].events[eventI].event_type << "\n";
    std::cout << arr2[arrI].events[eventI].cz_type << "\n";
    std::cout << arr2[arrI].events[eventI].cz_name << "\n";
    std::cout << arr2[arrI].events[eventI].injuries_direct << "\n";
    std::cout << arr2[arrI].events[eventI].injuries_indirect << "\n";
    std::cout << arr2[arrI].events[eventI].damage_property << "\n";
    std::cout << arr2[arrI].events[eventI].damage_crops << "\n";
    std::cout << arr2[arrI].events[eventI].tor_f_scale << "\n";
                                    
    if(arr2[arrI].events[eventI].f != NULL)         //If there is fatality info, print it
    {
        std::cout << arr2[arrI].events[eventI].f->fatality_id << "\n";
        std::cout << arr2[arrI].events[eventI].f->fatality_type << "\n";
        std::cout << arr2[arrI].events[eventI].f->fatality_date << "\n";
        std::cout << arr2[arrI].events[eventI].f->fatality_age << "\n";
        std::cout << arr2[arrI].events[eventI].f->fatality_sex << "\n";
        std::cout << arr2[arrI].events[eventI].f->fatality_location << "\n";
        if(arr2[arrI].events[eventI].f->next != NULL)
        {
            fatality_event* temp = arr2[arrI].events[eventI].f->next;
            while(temp->next != NULL)               //While there is a linked list of fatalities, print the details
            {
                std::cout << temp->fatality_id << "\n";
                std::cout << temp->fatality_type << "\n";
                std::cout << temp->fatality_date << "\n";
                std::cout << temp->fatality_age << "\n";
                std::cout << temp->fatality_sex << "\n";
                std::cout << temp->fatality_location << "\n";
                temp = temp->next;
            }
            std::cout << temp->fatality_id << "\n";
            std::cout << temp->fatality_type << "\n";
            std::cout << temp->fatality_date << "\n";
            std::cout << temp->fatality_age << "\n";
            std::cout << temp->fatality_sex << "\n";
            std::cout << temp->fatality_location << "\n";  
        }
    }
    std::cout << "\n";
    return;
}

/*
    The following function finds the number of max fatalities specified by the user
*/
void findMaxFatality(int number, std::string year, int* size, annual_storms* arr, int numYears, std::string type)
{
    if(year == "all")
    {
        int loopNum = 0;
        std::pair<int, int>* arr2 = buildArr(0, arr, size, numYears, type);
        for(int i = 0; i < numYears; i++)
        {
            loopNum = loopNum + size[i];
        }

        BUILDMAXHEAP(arr2, loopNum);

        for(int i = 0; i < number; i++)
        {
            std::pair<int, int> max = extractMax(arr2, loopNum);
            for(int i = 0; i < numYears; i++)
            {
                for(int j = 0; j < size[i]; j++)
                {
                    if(arr[i].events[j].event_id == max.first)
                    {
                        printDetails(arr, i, j);
                    }
                }
            }
            
        }
        delete[] arr2;
    }
    else
    {
        int yearVal = std::stoi(year);
        for(int i = 0; i < numYears; i++)
        {
            if(arr[i].year == yearVal)
            {
                std::pair<int, int>* arr2 = buildArr(yearVal, arr, size, numYears, type);
                BUILDMAXHEAP(arr2, size[i]);
                for(int j = 0; j < number; j++)
                {
                    std::pair<int, int> max = extractMax(arr2, size[i]);
                    for(int k = 0; k < size[i]; k++)
                    {
                        if(arr[i].events[k].event_id == max.first)
                        {
                            printDetails(arr, i, k);
                        }
                    }
                    
                    
                }
                delete[] arr2;
            }
        }
    }
    return;
}

/*
    The following function find the number of max damage type storms specified by the user
*/
void findMax(int number, std::string year, int* size, annual_storms* arr, int numYears, std::string type)
{
    if(year == "all")
    {
        int loopNum = 0;
        std::pair<int, int>* arr2 = buildArr(0, arr, size, numYears, type);
        for(int i = 0; i < numYears; i++)
        {
            loopNum = loopNum + size[i];
        }

        BUILDMAXHEAP(arr2, loopNum);

        for(int i = 0; i < number; i++)
        {
            std::pair<int, int> max = extractMax(arr2, loopNum);
            for(int i = 0; i < numYears; i++)
            {
                for(int j = 0; j < size[i]; j++)
                {
                    if(arr[i].events[j].event_id == max.first)
                    {
                        printDetails(arr, i, j);
                    }
                }
            }
            
        }
        delete[] arr2;
    }
    else
    {
        int yearVal = std::stoi(year);
        for(int i = 0; i < numYears; i++)
        {
            if(arr[i].year == yearVal)
            {
                std::pair<int, int>* arr2 = buildArr(yearVal, arr, size, numYears, type);
                BUILDMAXHEAP(arr2, size[i]);
                for(int j = 0; j < number; j++)
                {
                    std::pair<int, int> max = extractMax(arr2, size[i]); 
                    for(int k = 0; k < size[i]; k++)
                    {
                        if(arr[i].events[k].event_id == max.first)
                        {
                            printDetails(arr, i, k);
                        }
                    }
                }
                delete[] arr2;
            }
        }
        
    }
    return;
}

/*
    The following function would have found the range, but, you know.
*/
void range(std::string year, std::string field, std::string low, std::string high, int* size, int numYears, annual_storms* arr)
{
    
    if(year == "all")
    {
        std::cout << "Range function not completed\n";
    }
    else
    {
        std::cout << "Range function not completed\n";
    }
    
}

/*
    The following function builds a pair array for later use by the MAX-HEAPIFY function for find max queries
*/
std::pair<int, int>* buildArr(int year, annual_storms* arr, int* size, int numYears, std::string type)
{
    
    int allSize = 0;        //Size for all the years
    int yearSize = 0;       //Size for one year
    for(int i = 0; i < numYears; i++)
    {
        allSize = allSize + size[i];    //Getting size for all years
    }
    for(int i = 0; i < numYears; i++)
    {
        if(arr[i].year == year)
        {
            yearSize = size[i];         //Getting size for just one year
        }
    }

    if(year == 0)
    {
        int spot = 0;
        std::pair<int, int>* arr2 = new std::pair<int, int>[allSize];
        for(int i = 0; i < numYears; i++)
        {
            for(int j = 0; j < size[i]; j++)
            {
                if(type == "fatality")
                {
                    int count = 0;
                    arr2[spot + j].first = arr[i].events[j].event_id;
                    if(arr[i].events[j].f != NULL)
                    {
                        count++;
                        fatality_event* temp = new fatality_event;
                        temp = arr[i].events[j].f;
                        while(temp->next != NULL)
                        {
                            count++;
                            temp = temp->next;
                        }
                    }
                    arr2[spot + j].second = count;
                }
                if(type == "damage_crops" )
                {
                    arr2[spot + j].first = arr[i].events[j].event_id;
                    arr2[spot + j].second = arr[i].events[j].damage_crops;
                }

                if(type == "damage_property")
                {
                    arr2[spot + j].first = arr[i].events[j].event_id;
                    arr2[spot + j].second = arr[i].events[j].damage_property;
                }
                
            }
            spot = size[i];
        }
        return arr2;
    }
    else
    {
        int spot = 0;
        std::pair<int, int>* arr2 = new std::pair<int, int>[yearSize];
        for(int i = 0; i < numYears; i++)
        {   
            if(arr[i].year == year)
            {
                for(int j = 0; j < size[i]; j++)
                {
                    if(type == "fatality")
                    {
                        int count = 0;
                        arr2[spot + j].first = arr[i].events[j].event_id;
                        if(arr[i].events[j].f != NULL)
                        {
                            count++;
                            fatality_event* temp = new fatality_event;
                            temp = arr[i].events[j].f;
                            while(temp->next != NULL)
                            {
                                count++;
                                temp = temp->next;
                            }
                        }
                        arr2[spot + j].second = count;
                    }
                    if(type == "damage_crops" )
                    {
                        arr2[spot + j].first = arr[i].events[j].event_id;
                        arr2[spot + j].second = arr[i].events[j].damage_crops;
                    }

                    if(type == "damage_property")
                    {
                        arr2[spot + j].first = arr[i].events[j].event_id;
                        arr2[spot + j].second = arr[i].events[j].damage_property;
                    }
                }
            } 
            spot = size[i];    
        }
        return arr2; 
    }  
}

/*
    The following function extracts the max and restores the heap
*/
std::pair<int, int> extractMax(std::pair<int, int>* arr, int n)
{
    if(n < 1)
    {
        std::cout << "ERROR\n";
    }
    else
    {
        std::pair<int, int> max = arr[0];
        arr[0] = arr[n-1];
        MAXHEAPIFY(arr, 0, n-2);
        return max;
    }
    std::pair<int, int> bad;
    return bad;
    
}
/*
    The following function prints the details of a pair array (used for debugging)
*/
void printArr(std::pair<int, int>* arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        std::cout << arr[i].first << ": " << arr[i].second << " ";
    }
    std::cout << "\n";
}

/*
    The following function takes a pair array and builds a heap based off the second int in the pair
*/
void BUILDMAXHEAP(std::pair<int, int>* arr, int n)
{
    for(int i = (n-1)/2; i >= 0; i--)
    {
        MAXHEAPIFY(arr, i, n);
    }
}

/*
    The following function works to make a heap out of a pair array
*/
void MAXHEAPIFY(std::pair<int, int>* arr, int i, int n)
{
    int largest;
    int l = LEFT(i);
    int r = RIGHT(i);
    if(l < n && arr[l].second > arr[i].second)
    {
        largest = l;
    }
    else
    {
        largest = i;        
    }
    if(r < n && arr[r].second > arr[largest].second)
    {
        largest = r;
    }
    if(largest != i)
    {
        swap(arr[i], arr[largest]);
        MAXHEAPIFY(arr, largest, n);
    }
    
}

/*
    The following function is a nonfunctional block that would have been used for range, but, you know.
*/
void Insert(bst *&root, std::string newS, int newID, std::string low, std::string high) 
{
    if(root == NULL)
    {
        bst* root = new bst;
        int length = newS.length();
        char charArr[length + 1];
        strcpy(charArr, newS.c_str());
        root->s = charArr;
        root->event_id = newID;
        root->left = NULL;
        root->right = NULL;
        return;
    }
    else if (newS < root->s) 
    {
        Insert(root->left, newS, newID, low, high);
    }
    else if(newS > root->s) 
    {
        Insert(root->right, newS, newID, low, high);
    }
    else 
    {
        if(newID < root->event_id)
        {
            Insert(root->left, newS, newID, low, high);
        }
        if(newID > root->event_id)
        {
            Insert(root->right, newS, newID, low, high);
        }
    }
}

/*
    The following blocks are used for the MAX-HEAP
*/
int PARENT(int i)
{return i/2;}
int LEFT(int i)
{return 2*i + 1;}
int RIGHT(int i)
{return (2*(i + 1));}


//END OF PROGRAM
//ONLY 963 lines, wow!