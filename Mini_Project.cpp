#include<iostream>
#include <fstream>                                //  file class 
#include<cstring>                                 
 
#define PASSWORD_FILE "Password_miniproject.txt"

using namespace std;

class program_password{
    private:
    static const int DEFAULT_PASSWORD = 1234;

    private:
    int password;

    public:                                                          // File Handling
    program_password() {
        password = DEFAULT_PASSWORD;
        loadPassword();
    }

    bool authenticate() {
        int pass;
        cout << "Enter password: ";
        cin >> pass;
        return match(pass);
    }

    bool match(int pass) {
        return pass == password;
    }

    void loadPassword() {
        ifstream fin;                                      
        fin.open(PASSWORD_FILE);
        fin.read((char*)&password, sizeof(password));
        fin.close();
    }

    void savePassword() {
        ofstream fout;
        fout.open(PASSWORD_FILE);
        fout.write((char*)&password, sizeof(password));
        fout.close();
    }

    void change_password(){
        int old_pass;
        cout << "\tEnter Old Password:"<<endl;
        cin >> old_pass;
        if(!match(old_pass)) {
            cout<<"\tPassword Mismatch"<<endl;
            return;
        }

        cout<<"\tEnter New Password:"<<endl;
        cin >> password;
        cout<<"\tPassword Changed successfully !!!"<<endl;
        savePassword();
    }
};

class Hospital_info{
    
    protected:
        string hospital_name; 
        string hospital_location;
        long long int contact_no;
        int no_of_doctors;
        int total_beds;
    public:

    static int no_of_beds;

    Hospital_info(){
        hospital_name="Pune Central Hospital";
        hospital_location="Pune";
        contact_no=9876543210;
        no_of_doctors=10;
        total_beds=25;
    }
    
    void display_info(){
        cout<<"\tName of Hospital: ";
        cout<<hospital_name<<endl;

        cout<<"\tLocation: ";
        cout<<hospital_location<<endl;

        cout<<"\tContact Number: ";
        cout<<contact_no<<endl;

        cout<<"\tNumber of Doctors: ";
        cout<<no_of_doctors<<endl;

        cout<<"\tNumber of Beds: ";;
        cout<<no_of_beds<<endl;
    }

    virtual void getdata()=0;             //pure virtual function

    static void patient_added(){          // Static function 
        no_of_beds=no_of_beds-1;
    };

    static void patient_discharge(){
        no_of_beds=no_of_beds+1;
    }
};



int Hospital_info::no_of_beds=25;      //Static variable 


class patient_info:public Hospital_info{                  

    public:    
        
        char name[100];
        char address[100];
        float age;
        char gender[10];
        
    void getdata(){                                          // Polymorphism
        cout<<"\n\tEnter Name of Patient:"<<endl;
        cin>>name;
        cout<<"\tEnter Address of Patient:"<<endl;
        cin>>address;
        cout<<"\tEnter Age of Patient:"<<endl;
        cin>> age;
        cout<<"\tEnter Gender of Patient:"<<endl;             //inline function 
        cin>> gender;
    }

    virtual void show_data()=0;
};

class prescription:public patient_info{                   
        protected:

        int ward;
        int bed_no;
        char doctor[100];

        public:
        char disease[100];

    void presc(){
        cout<<"\tSelect Ward: 1.IPD 2.Emergency 3.Labour Room 4.Casualty Ward"<<endl;
        cin>>ward;
        cout<<"\tEnter Disease:"<<endl;
        cin>>disease;
        cout<<"\tEnter Bed Number:"<<endl;
        cin>>bed_no;
        cout<<"\tName of Doctor appointed:"<<endl;
        cin>>doctor;
    }    

};

class Medicine:public prescription{                           //Multilevel inheritance
    
    public:
    string medicine_name[100];
    int option;
    int i=0;
    int n=1;
    void get_med_info(){

     do{
        cout<<"\tEnter Name of Medicine "<<(i+1)<<":"<<endl;
        cin>>medicine_name[i];
        i++;
        n++;
        cout<<"\tDo you want to add more Medicine: 1.Yes 2.No"<<endl;
        cin>>option;
     }while(option==1);

    }
    
    void show_data(){
        cout<<"\tName of Patient:"<<name<<endl;
        cout<<"\tAddress of Patient:"<<address<<endl;
        cout<<"\tAge of Patient:"<<age<<endl;
        cout<<"\tGender of Patient:"<<gender<<endl;
        cout<<"\tWard Given:";
        switch(ward){
            case 1:cout<<"IPD"<<endl;
            break;
            case 2:cout<<"Emergency Ward"<<endl;
            break;
            case 3:cout<<"Labor Room"<<endl;
            break;
            case 4:cout<<"Casualty Ward"<<endl;
            break;}
        cout<<"\tDisease:"<<disease<<endl;
        cout<<"\tBed Number:"<<bed_no<<endl;
        cout<<"\tName of Doctor appointed:"<<doctor<<endl;

    }
    void show_med_info(){
        cout<<"\tMedicine Given:"<<endl;
        for(i=0;i<n-1;i++){
            cout<<"\t"<<(i+1)<<"]"<<medicine_name[i]<<endl;
        }
    }
};

int main(){
    
    program_password pass;                            // Object
   
    Medicine object[100];                             // Array of objects
    
    Hospital_info *obj;
    Medicine obj2;                          
    obj=& obj2;                                       // Upcasting(pointers)
    

    cout<<"\n\n\t\t\t\t\t*Pune Central Hospital*"<<endl;

    
    int password1,password2,new_password,j,k,l,opt,ch;
   
    char search[100];
    char disease_search[100];
    
    
    if(pass.authenticate()) {    
        j=0,k=0,l=0;
        while(1) {
            cout<<"\n\tSelect an Option:"<<endl;
            cout<<"\t1.Add patient's Information."<<endl;
            cout<<"\t2.Show Patient's Information."<<endl;
            cout<<"\t3.Search Patient."<<endl;
            cout<<"\t4.Search Patient By disease."<<endl;
            cout<<"\t5.Bed Available."<<endl;
            cout<<"\t6.More Information About Hospital"<<endl;
            cout<<"\t7.Change Password"<<endl;

            cin>>opt;
            
            switch (opt) {
            case 1:
            do{
                
                object[j].getdata();
                object[j].presc();
                object[j].get_med_info(); 
                j++;
                Hospital_info::patient_added();
                cout<<"\tWant to Add more patient:1.Yes 2.No"<<endl;
                cin>>ch;
            }while(ch==1);
                break;
            
            case 2:
            while(k<j){
                object[k].show_data();
                object[k].show_med_info();
                k++;
            }

                break;
            
            case 3:
                    
                    int flag;
                    cout<<"\tEnter a Name you that want to search"<<endl;
                    cin>>search;
                    while(l<j){
                        flag= strcmp(search,object[l].name);
                        l++;
                    if(flag==0){
                    cout<<"\tInformation Found:"<<endl;
                    object[l-1].show_data();
                    object[l-1].show_med_info();
                    break;}
                    
                    }
                    if(flag!=0){cout<<"\tInformation Not Found"<<endl;}
                break;

            case 4:
                    int flag1;
                    cout<<"\tEnter a Name of disease that want to search"<<endl;
                    cin>>disease_search;
                    while(l<j){
                        flag1= strcmp(disease_search,object[l].disease);
                        l++;
                    if(flag1==0){
                    cout<<"\tInformation Found:"<<endl;
                    object[l-1].show_data();
                    object[l-1].show_med_info();
                    flag1=10;}
                    }
                    if(flag1!=10){cout<<"\tPatients with this disease Not Found"<<endl;}
                break;


            case 5:
                    if(Hospital_info::no_of_beds>0){
                        cout<<"\tNumber of beds Available:"<<Hospital_info::no_of_beds<<endl;}
                    try{                                         
                        if(Hospital_info::no_of_beds<0){
                            throw Hospital_info::no_of_beds;                   //Exception Handling 
                        }
                    }catch(...){
                        cout<<"\tSorry beds are Not available "<<endl;            
                    }
                    
                break;
            
            case 6:
                
                obj->display_info();      
                cout<<endl;
                break;
            
            case 7:
                pass.change_password();
                if(!pass.authenticate()) {
                    cout << "\tInvalid Password !! Access Denied";
                    return 0;
                }
                break;
            }
        }
    }

   else{
        cout<<"\tInvalid Password !! Access Denied";
    }

}