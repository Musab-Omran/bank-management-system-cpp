#pragma once

#include<iostream>
#include<string>
#include "clsString.h"
#include <fstream>
#include "GlobalVariables.h"


class clsCurrency
{
    
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;

    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;


    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#")
    {
        string* vCurrencyData;
        int size = 0;
        vCurrencyData = clsString::Split(Line, Seperator, size);

        clsCurrency x = clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
            stod(vCurrencyData[3]));

        delete[] vCurrencyData;

        return x;
    }

    static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {

        string stCurrencyRecord = "";
        stCurrencyRecord += Currency.Country() + Seperator;
        stCurrencyRecord += Currency.CurrencyCode() + Seperator;
        stCurrencyRecord += Currency.CurrencyName() + Seperator;
        stCurrencyRecord += to_string(Currency.Rate());

        return stCurrencyRecord;

    }

    static  clsCurrency* _LoadCurrencysDataFromFile()
    {

        clsCurrency* vCurrencys = new clsCurrency[NumberOfCurrencies];

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            int i = 0;
            string Line;

            while (getline(MyFile, Line))
            {
                if (i >= NumberOfCurrencies)
                    break;

                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

                vCurrencys[i] = (Currency);
                i++;
            }

            MyFile.close();

        }

        return vCurrencys;

    }

    static void _SaveCurrencyDataToFile(clsCurrency* vCurrencys)
    {

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (int i = 0; i < NumberOfCurrencies; i++)
            {
                DataLine = _ConverCurrencyObjectToLine(vCurrencys[i]);
                MyFile << DataLine << endl;
            }

            MyFile.close();

        }

    }

    void _Update()
    {
        clsCurrency* _vCurrencys;
        _vCurrencys = _LoadCurrencysDataFromFile();

        for (int i = 0; i < NumberOfCurrencies; i++)
        {
            if (_vCurrencys[i].CurrencyCode() == CurrencyCode())
            {
                _vCurrencys[i] = *this;
                break;
            }

        }

        _SaveCurrencyDataToFile(_vCurrencys);

        delete[] _vCurrencys;
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:

    clsCurrency() {

    }

    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    static clsCurrency* GetAllUSDRates()
    {

        return _LoadCurrencysDataFromFile();

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string Country()
    {
        return _Country;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    string CurrencyName()
    {
        return _CurrencyName;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    float Rate()
    {
        return _Rate;
    }


    static clsCurrency FindByCode(string CurrencyCode)
    {

        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();

    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }

            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();

    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
        return (!C1.IsEmpty());

    }

    static clsCurrency* GetCurrenciesList()
    {
        return _LoadCurrencysDataFromFile();
    }

    float ConvertToUSD(float Amount)
    {
        return (float)(Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }

        return (float)(AmountInUSD * Currency2.Rate());

    }

};
