#ifndef FRACTION_A_FRACTION_HPP
#define FRACTION_A_FRACTION_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
using namespace std;

namespace ariel{

    class Fraction
    {
        private:
            int numerator;
            int denominator;

        public:
            Fraction(int numerator, int denominator);
            Fraction(float number);
            Fraction();

            int getNumerator();
            int getDenominator();
            void SetNumerator(int numerator);
            void SetDenominator(int denominator);
            

            Fraction operator+(Fraction const& other) const;
            Fraction operator+(const float& other){
                //if other is zero then we can transfer it to fraction so we just return *this
                if(1 - other == 1.0){
                    return *this;
                }
                Fraction fraction = this->transfer(other);
                return *this + fraction;
            }
            friend Fraction operator+(const float& left, const Fraction& right);

            Fraction operator-(const Fraction& other) const;
            Fraction operator-(const float& other){
                //if other is zero then we can transfer it to fraction so we just return *this
                if(1 - other == 1.0){
                    return *this;
                }
                Fraction fraction = this->transfer(other);
                return *this - fraction;
            }
            friend Fraction operator-(const float& left, const Fraction& right);

            Fraction operator*(const Fraction& other) const;
            Fraction operator*(const float& other) const{
                //if other is zero then we cant transfer it to fraction so we just return *this
                if(1 - other == 1.0){
                    return Fraction{0,1};
                }
                Fraction fraction = this->transfer(other);
                return *this * fraction;
            }
            friend Fraction operator*(const float& left, const Fraction& right);
                
            Fraction operator/(const Fraction& other) const;
            Fraction operator/(const float& other) const{
                Fraction fraction = this->transfer(other);
                return *this / fraction;
            }
            friend Fraction operator/(const float& left, const Fraction& right);

            bool operator==(const Fraction& other) const;
            bool operator==(const float& other) const{
                Fraction fraction = this->transfer(other);
                return (fraction == *this);
            }
            friend bool operator==(const float& left, const Fraction& right);

            bool operator>(const Fraction& other) const;
            bool operator>(const float& other) const{
                Fraction fraction = this->transfer(other);
                return (*this > fraction);
            }
            friend bool operator>(const float& left, const Fraction& right);

            bool operator>=(const Fraction& other) const;
            bool operator>=(const float& other) const{
                Fraction fraction = this->transfer(other);
                return (*this >= fraction);
            }
            friend bool operator>=(const float& left, const Fraction& right);

            bool operator<(const Fraction& other) const;
            bool operator<(const float& other) const{
                Fraction fraction = this->transfer(other);
                return (*this < fraction);
            }
            friend bool operator<(const float& left, const Fraction& right);

            bool operator<=(const Fraction& other) const;
            bool operator<=(const float& other) const{
                Fraction fraction = this->transfer(other);
                return (*this <= fraction);
            }
            friend bool operator<=(const float& left, const Fraction& right);

            Fraction operator ++();
            Fraction operator --();

            Fraction operator ++(int);
            Fraction operator --(int);
            
            friend ostream& operator<<(ostream& ostream, Fraction& Frac);
            friend istream& operator>>( istream& input, Fraction& Frac);

            int gcd(int num1, int num2) const;
            int lcm(int num1, int num2) const;

        
            Fraction transfer(float number) const;
            // Reduces the fraction
            // minus will always appear in the denominator
            Fraction reduction(Fraction& fraction) const;

        };
    
}

#endif