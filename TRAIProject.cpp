#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

class CSVRow {
public:
    std::string date;
    std::string company;
    std::string spectrumRange;
    std::string circle;
    int revenue;

    CSVRow(const std::string& d, const std::string& c, const std::string& sr, const std::string& cir, int rev)
        : date(d), company(c), spectrumRange(sr), circle(cir), revenue(rev) {}

    
    bool operator<(const CSVRow& other) const {
        if (circle == other.circle) {
            return company < other.company;
        }
        return circle < other.circle;
    }
};

class CSVRow1 {
public:
    std::string date1;
    std::string company1;
    std::string location1;
    int subscribers;

    CSVRow1(const std::string& d, const std::string& c, const std::string& loc, int subs)
        : date1(d), company1(c), location1(loc), subscribers(subs) {}

    bool operator<(const CSVRow1& other) const {
        if (company1 == other.company1) {
            return location1 < other.location1;
        }
        return company1 < other.company1;
    }
};


class CSVRow2 {
public:
    std::string date2;
    std::string MVONcompany;
    std::string location2;
    int Request;

    CSVRow2(const std::string& d, const std::string& MVONc, const std::string& loc, int req)
        : date2(d), MVONcompany(MVONc), location2(loc), Request(req) {}

    bool operator<(const CSVRow2& other) const {
        if (MVONcompany == other.MVONcompany) {
            return location2 < other.location2;
        }
        return MVONcompany < other.MVONcompany;
    }
};

class CSVDataManager {
public:
    std::vector<CSVRow> data;
    std::vector<CSVRow1> data1;
    std::vector<CSVRow2> data2;

    bool readCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            return false;
        }

        data.clear();

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string date, company, spectrumRange, circle;
            int revenue;


            std::getline(ss, date, ',');
            std::getline(ss, company, ',');
            std::getline(ss, spectrumRange, ',');
            std::getline(ss, circle, ',');
            ss >> revenue;

            data.emplace_back(date, company, spectrumRange, circle, revenue);
        }

        return true;
    }

    bool readCSV1(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            return false;
        }

        data1.clear();

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string date1, company1, location1;
            int subscribers;

            std::getline(ss, date1, ',');
            std::getline(ss, company1, ',');
            std::getline(ss, location1, ',');
            ss >> subscribers;

            data1.emplace_back(date1, company1, location1, subscribers);
        }

        return true;
    }


     bool readCSV2(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            return false;
        }

        data2.clear();

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string date2, MVONcompany, location2;
            int Request;

            std::getline(ss, date2, ',');
            std::getline(ss, MVONcompany, ',');
            std::getline(ss, location2, ',');
            ss >> Request;

            data2.emplace_back(date2, MVONcompany, location2, Request);
        }

        return true;
    }

        void sortDataByCircleAndCompany() {
        std::sort(data.begin(), data.end());
    }

        void sortDataByCompanyAndLocation() {
        std::sort(data1.begin(), data1.end());
    }


        void sortDataByMVONCompanyAndLocation() {
        std::sort(data2.begin(), data2.end());
    }


    bool writeSortedCSV(const std::string& filename) {
        std::ofstream file(filename);
        if (!file) {
            return false;
        }

        for (const CSVRow& row : data) {
            file << row.date << ',' << row.company << ',' << row.spectrumRange << ',' << row.circle << ',' << row.revenue << '\n';
        }


        for (const CSVRow1& row : data1) {
            file << row.date1 << ',' << row.company1 << ',' << row.location1 << ',' << row.subscribers << '\n';
        }


         for (const CSVRow2& row : data2) {
            file << row.date2 << ',' << row.MVONcompany << ',' << row.location2 << ',' << row.Request << '\n';
        }


        return true;
    }

    void displaySortedData() {
        for (const CSVRow& row : data) {
            std::cout << row.date << ',' << row.company << ',' << row.spectrumRange << ',' << row.circle << ',' << row.revenue << '\n';
        }
    }
    
    void displaySortedData1() {
        for (const CSVRow1& row : data1) {
            std::cout << row.date1 << ',' << row.company1 << ',' << row.location1 << ',' << row.subscribers << '\n';
        }
    }

    void displaySortedData2() {
        for (const CSVRow2& row : data2) {
            std::cout << row.date2 << ',' << row.MVONcompany << ',' << row.location2 << ',' << row.Request << '\n';
        }
    }


    int sum(const std::string& companyToFind, const std::string& circleToFind) {
        int sum = 0;

        for (const CSVRow& row : data) {
            if (row.company == companyToFind && row.circle == circleToFind) {
                // Assuming that "spectrumRange" is in the format of "X MHz" where X is an integer
                // Extract the numeric part and add it to the sum
                int spectrumValue = std::stoi(row.spectrumRange);
                sum += spectrumValue;
            }
        }
        return sum;
    }


    int subscribersum(const std::string& company1, const std::string& location1) {
        int sum = 0;
        for (const CSVRow1& row : data1) {
            if (row.company1 == company1 && row.location1 == location1) {
                sum += row.subscribers;
            }
        }
        return sum;
    }
    
    double density(const std::string &companyToFind, const std::string &circleToFind){
    double subs,width;

    subs= subscribersum(companyToFind,circleToFind);
    width=sum(companyToFind,circleToFind);


    if (subs == 0) {
     return 0;  // To avoid division by zero
    }

      return width/subs;

    }
    
   void densitycomp(const std::string &companyToFind, const std::string &circleToFind){
        std::ofstream file("Biding_database.csv", std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Failed to create the file!" << std::endl;
        }
        
        
        double userdensct;
        double threshold= 0.025;
        userdensct= density(companyToFind,circleToFind);
        if(threshold>userdensct){
        std::cout<<circleToFind<<":  "<<companyToFind<<" is allowed for bid"<<"\n "<<std::endl;
        file<<circleToFind<<":  "<<companyToFind<<" : is allowed for bid"<<std::endl;
            
        }
        else {
        std::cout<<circleToFind<<":  "<<companyToFind<<" is not allowed for bid"<<"\n "<<std::endl;
        file<<circleToFind<<":  "<<companyToFind<<" : is not allowed for bid"<<std::endl;
        }  

        file.close();

    }

};

int main() {
    
    CSVDataManager dataManager;

   int x;
    std::cout<<"1. spectrumRange file and subscriber file"<<std::endl;
    
    std::cout<<"2. MVONSpectrum file"<< std::endl;
    std::cout<<"Enter the number which you want to print"<<std::endl;
    std::cin>>x;

    if (x==1){

        dataManager.readCSV("spectrumRange.csv");
        dataManager.sortDataByCircleAndCompany();
        std::cout << "Sorted Spectrum Range Data: "<<"\n"<<std::endl;
        dataManager.displaySortedData();
        std::cout<<"\n  "<<std::endl;
        

        
        dataManager.readCSV1("subscribers.csv");
        dataManager.sortDataByCompanyAndLocation();
        std::cout << "Sorted Subscribers Data: "<<"\n"<<std::endl;
        dataManager.displaySortedData1();

    }


    if (x==2){
        dataManager.readCSV2("MVNOSpectrum.csv");
        dataManager.sortDataByMVONCompanyAndLocation();
        std::cout << "Sorted MVNOCompany Data:"<<"\n"<<std::endl;
        dataManager.displaySortedData2(); 
       }

        std::cout<<" \n"<<std::endl;
        int p;
        std::cout<<"enter the city name"<<std::endl<<"1. Chandigarh"<<std::endl<<"2. Jaipur"<<std::endl<<"3. Delhi"<<std::endl<<"4. Lucknow"<<std::endl<<"5. Patna"<<std::endl<<"6. Kolkata"<<std::endl;
        std::cout<<"Select the City for Information"<<"\n"<<std::endl;
        std::cin>>p;
 
        if(p==1){
        std::cout << "Sum of Spectrum Range for Airtel in Chandigarh : " << dataManager.sum("Airtel", "Chandigarh") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for BSNL in Chandigarh : " << dataManager.sum("BSNL" , "Chandigarh") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Jio in Chandigarh : " << dataManager.sum("Jio" , "Chandigarh") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Vodafone in Chandigarh : " << dataManager.sum("Vodafone" , "Chandigarh") << " MHz" <<"\n "<< std::endl;
        


        std::cout << "Sum of Subscribers for Airtel in Chandigarh :  " << dataManager.subscribersum("Airtel" , "Chandigarh") <<std::endl;
        std::cout << "Sum of Subscribers for BSNL in Chandigarh :  " << dataManager.subscribersum("BSNL" , "Chandigarh") <<std::endl;
        std::cout << "Sum of Subscribers for Jio in Chandigarh :  " << dataManager.subscribersum("Jio" , "Chandigarh") <<std::endl;
        std::cout << "Sum of Subscribers for Vodafone in Chandigarh :  " << dataManager.subscribersum("Vodafone" , "Chandigarh") <<"\n "<<std::endl;



        std::cout<<"usage density of airtel in Chandigarh "<<dataManager.density("Airtel", "Chandigarh")<<std::endl;
        std::cout<<"usage density of BSNL in Chandigarh "<<dataManager.density("BSNL", "Chandigarh")<<std::endl;
        std::cout<<"usage density of Jio in Chandigarh "<<dataManager.density("Jio", "Chandigarh")<<std::endl;
        std::cout<<"usage density of Vodafone in Chandigarh "<<dataManager.density("Vodafone", "Chandigarh")<<"\n "<<std::endl;
        
        
        dataManager.densitycomp("Airtel", "Chandigarh");
        dataManager.densitycomp("BSNL", "Chandigarh");
        dataManager.densitycomp("Jio", "Chandigarh");
        dataManager.densitycomp("Vodafone", "Chandigarh");


        }


        if(p==2){
        std::cout << "Sum of Spectrum Range for Airtel in Jaipur: " << dataManager.sum("Airtel", "Jaipur") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for BSNL in Jaipur : " << dataManager.sum("BSNL" , "Jaipur") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Jio in Jaipur : " << dataManager.sum("Jio" , "Jaipur") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Vodafone in Jaipur : " << dataManager.sum("Vodafone" , "Jaipur") << " MHz" <<"\n "<< std::endl;
        


        std::cout << "Sum of Subscribers for Airtel in Jaipur :  " << dataManager.subscribersum("Airtel" , "Jaipur") <<std::endl;
        std::cout << "Sum of Subscribers for BSNL in Jaipur :  " << dataManager.subscribersum("BSNL" , "Jaipur") <<std::endl;
        std::cout << "Sum of Subscribers for Jio in Jaipur :  " << dataManager.subscribersum("Jio" , "Jaipur") <<std::endl;
        std::cout << "Sum of Subscribers for Vodafone in Jaipur :  " << dataManager.subscribersum("Vodafone" , "Jaipur")<<"\n " <<std::endl;



        std::cout<<"usage density of airtel in Jaipur "<<dataManager.density("Airtel", "Jaipur")<<std::endl;
        std::cout<<"usage density of BSNL in Jaipur "<<dataManager.density("BSNL", "Jaipur")<<std::endl;
        std::cout<<"usage density of Jio in Jaipur "<<dataManager.density("Jio", "Jaipur")<<std::endl;
        std::cout<<"usage density of Vodafone in Jaipur "<<dataManager.density("Vodafone", "Jaipur")<<"\n "<<std::endl;

        
        dataManager.densitycomp("Airtel", "Jaipur");
        dataManager.densitycomp("BSNL", "Jaipur");
        dataManager.densitycomp("Jio", "Jaipur");
        dataManager.densitycomp("Vodafone", "Jaipur");
        }

        if(p==3){

        std::cout << "Sum of Spectrum Range for Airtel in Delhi: " << dataManager.sum("Airtel", "Delhi") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for BSNL in Delhi : " << dataManager.sum("BSNL" , "Delhi") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Jio in Delhi : " << dataManager.sum("Jio" , "Delhi") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Vodafone in Delhi : " << dataManager.sum("Vodafone" , "Delhi") << " MHz" <<"\n "<< std::endl;
        


        std::cout << "Sum of Subscribers for Airtel in Delhi :  " << dataManager.subscribersum("Airtel" , "Delhi") <<std::endl;
        std::cout << "Sum of Subscribers for BSNL in Delhi :  " << dataManager.subscribersum("BSNL" , "Delhi") <<std::endl;
        std::cout << "Sum of Subscribers for Jio in Delhi :  " << dataManager.subscribersum("Jio" , "Delhi") <<std::endl;
        std::cout << "Sum of Subscribers for Vodafone in Delhi :  " << dataManager.subscribersum("Vodafone" , "Delhi") <<"\n "<<std::endl;



        std::cout<<"usage density of airtel in delhi "<<dataManager.density("Airtel", "Delhi")<<std::endl;
        std::cout<<"usage density of BSNL in delhi "<<dataManager.density("BSNL", "Delhi")<<std::endl;
        std::cout<<"usage density of Jio in delhi "<<dataManager.density("Jio", "Delhi")<<std::endl;
        std::cout<<"usage density of Vodafone in delhi "<<dataManager.density("Vodafone", "Delhi")<<"\n "<<std::endl;


        
        dataManager.densitycomp("Airtel", "Delhi");
        dataManager.densitycomp("BSNL", "Delhi");
        dataManager.densitycomp("Jio", "Delhi");
        dataManager.densitycomp("Vodafone", "Delhi");
        

    }

    if(p==4){

        std::cout << "Sum of Spectrum Range for Airtel in Lucknow: " << dataManager.sum("Airtel", "Lucknow") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for BSNL in Lucknow : " << dataManager.sum("BSNL" , "Lucknow") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Jio in Lucknow : " << dataManager.sum("Jio" , "Lucknow") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Vodafone in Lucknow : " << dataManager.sum("Vodafone" , "Lucknow") << " MHz" <<"\n "<< std::endl;
        


        std::cout << "Sum of Subscribers for Airtel in Lucknow :  " << dataManager.subscribersum("Airtel" , "Lucknow") <<std::endl;
        std::cout << "Sum of Subscribers for BSNL in Lucknow :  " << dataManager.subscribersum("BSNL" , "Lucknow") <<std::endl;
        std::cout << "Sum of Subscribers for Jio in Lucknow :  " << dataManager.subscribersum("Jio" , "Lucknow") <<std::endl;
        std::cout << "Sum of Subscribers for Vodafone in Lucknow :  " << dataManager.subscribersum("Vodafone" , "Lucknow") <<"\n "<<std::endl;


        std::cout<<"usage density of airtel in Lucknow "<<dataManager.density("Airtel", "Lucknow")<<std::endl;
        std::cout<<"usage density of BSNL in Lucknow "<<dataManager.density("BSNL", "Lucknow")<<std::endl;
        std::cout<<"usage density of Jio in Lucknow "<<dataManager.density("Jio", "Lucknow")<<std::endl;
        std::cout<<"usage density of Vodafone in Lucknow "<<dataManager.density("Vodafone", "Lucknow")<<"\n "<<std::endl;


        
        dataManager.densitycomp("Airtel", "Lucknow");
        dataManager.densitycomp("BSNL", "Lucknow");
        dataManager.densitycomp("Jio", "Lucknow");
        dataManager.densitycomp("Vodafone", "Lucknow");

    }
    

    if(p==5){

        std::cout << "Sum of Spectrum Range for Airtel in Patna: " << dataManager.sum("Airtel", "Patna") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for BSNL in Patna : " << dataManager.sum("BSNL" , "Patna") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Jio in Patna : " << dataManager.sum("Jio" , "Patna") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Vodafone in Patna : " << dataManager.sum("Vodafone" , "Patna") << " MHz" <<"\n "<< std::endl;
        


        std::cout << "Sum of Subscribers for Airtel in Patna :  " << dataManager.subscribersum("Airtel" , "Patna") <<std::endl;
        std::cout << "Sum of Subscribers for BSNL in Patna :  " << dataManager.subscribersum("BSNL" , "Patna") <<std::endl;
        std::cout << "Sum of Subscribers for Jio in Patna :  " << dataManager.subscribersum("Jio" , "Patna") <<std::endl;
        std::cout << "Sum of Subscribers for Vodafone in Patna :  " << dataManager.subscribersum("Vodafone" , "Patna") <<"\n "<<std::endl;


        std::cout<<"usage density of airtel in Patna "<<dataManager.density("Airtel", "Patna")<<std::endl;
        std::cout<<"usage density of BSNL in Patna "<<dataManager.density("BSNL", "Patna")<<std::endl;
        std::cout<<"usage density of Jio in Patna "<<dataManager.density("Jio", "Patna")<<std::endl;
        std::cout<<"usage density of Vodafone in Patna "<<dataManager.density("Vodafone", "Patna")<<"\n "<<std::endl;
        

        
        dataManager.densitycomp("Airtel", "Patna");
        dataManager.densitycomp("BSNL", "Patna");
        dataManager.densitycomp("Jio", "Patna");
        dataManager.densitycomp("Vodafone", "Patna");
    }


    if(p==6){

        std::cout << "Sum of Spectrum Range for Airtel in Kolkata: " << dataManager.sum("Airtel", "Kolkata") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for BSNL in Kolkata : " << dataManager.sum("BSNL" , "Kolkata") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Jio in Kolkata : " << dataManager.sum("Jio" , "Kolkata") << " MHz" << std::endl;
        std::cout << "Sum of Spectrum Range for Vodafone in Kolkata : " << dataManager.sum("Vodafone" , "Kolkata") << " MHz" <<"\n "<< std::endl;
        
        std::cout << "Sum of Subscribers for Airtel in Kolkata :  " << dataManager.subscribersum("Airtel" , "Kolkata") <<std::endl;
        std::cout << "Sum of Subscribers for BSNL in Kolkata :  " << dataManager.subscribersum("BSNL" , "Kolkata") <<std::endl;
        std::cout << "Sum of Subscribers for Jio in Kolkata :  " << dataManager.subscribersum("Jio" , "Kolkata") <<std::endl;
        std::cout << "Sum of Subscribers for Vodafone in Kolkata :  " << dataManager.subscribersum("Vodafone" , "Kolkata") <<"\n "<<std::endl;

        std::cout<<"usage density of airtel in Kolkata "<<dataManager.density("Airtel", "Kolkata")<<std::endl;
        std::cout<<"usage density of BSNL in Kolkata "<<dataManager.density("BSNL", "Kolkata")<<std::endl;
        std::cout<<"usage density of Jio in Kolkata "<<dataManager.density("Jio", "Kolkata")<<std::endl;
        std::cout<<"usage density of Vodafone in Kolkata "<<dataManager.density("Vodafone", "Kolkata")<<"\n "<<std::endl;

        dataManager.densitycomp("Airtel", "Kolkata");
        dataManager.densitycomp("BSNL", "Kolkata");
        dataManager.densitycomp("Jio", "Kolkata");
        dataManager.densitycomp("Vodafone", "Kolkata");

    }
        return 0;
}

