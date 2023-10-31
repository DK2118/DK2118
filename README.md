Topic:
CSV Data Analysis and Bidding Decision System.

This C++ program reads and analyzes data from multiple CSV files containing information about telecommunications companies, their spectrum ranges, subscribers, and location data. It then calculates usage density and provides a bidding decision for each company based on certain criteria. Here's a simple readme for this code.

Table of Contents:

1. Introduction
2. Usage
3. Data Files
4. Program Overview
5. Functionality
6. Sample Output

Introduction:
This C++ program processes data from three different CSV files:

>>spectrumRange.csv: Contains information about telecom companies, their spectrum ranges, and revenues.
>>subscribers.csv: Contains information about telecom companies, their locations, and the number of subscribers.
>>MVNOSpectrum.csv: Contains data related to MVNO (Mobile Virtual Network Operator) companies, their locations, and requests.

The program provides the following functionalities:

> It sort data by using different criteria.
> Calculates the sum of spectrum ranges and subscribers for a given company and location.
> Computes usage density for each company.
> Makes a bidding decision for companies based on usage density.

Data Files

The program requires three CSV data files with specific formats:

spectrumRange.csv.
> It contains Columns of: Date, Company, SpectrumRange, Circle, Revenue.

subscribers.csv.
> It contains Columns of: Date1, Company1, Location1, Subscribers.

MVNOSpectrum.csv
> It contains Columns of: Date2, MVONCompany, Location2, Request.

Program Overview:

The program performs the following tasks:

> Reads data from CSV files.
> Sorts data based on specific criteria.
> Calculates the sum of spectrum ranges and subscribers for given companies and locations.
> Computes the usage density for each company in a specific location.
> Makes a bidding decision for each company based on the usage density.

Functionality:

The program offers the following functionalities:

> Sort data by different criteria:
> Sort spectrum data by "Circle" and then "Company".
> Sort subscriber data by "Company" and then "Location".
> Sort MVNO data by "Company" and then "Location".
> Calculate the sum of spectrum ranges and subscribers for a given company and location:
> Calculate the sum of spectrum ranges for a specific company and location.
> Calculate the sum of subscribers for a specific company and location.
> Calculate usage density:
> Calculate the usage density for a specific company and location.
> Make bidding decisions:
> Determine whether a company is allowed to bid based on a predefined threshold for usage      density.

Sample Output:

The program displays the following information for each company and location:

> Sum of spectrum range (in MHz).
> Sum of subscribers.
> Usage density.
> Bidding decision (allowed or not allowed).







