#include "Fraction.hpp"
#include <math.h>
using namespace std;


namespace ariel{
    /*
    ==================================================
                Geters and Seters
    ==================================================
    */

    int Fraction::getNumerator(){
            return this->numerator;
    }

    int Fraction::getDenominator(){
        return this->denominator;
    }

    void Fraction::SetNumerator(int numerator){
        this->numerator = numerator;
    }

    void Fraction::SetDenominator(int denominator){
        if(denominator == 0){
            throw std::invalid_argument("dividing by zero exeption");
        }else{
            this->denominator = denominator;
        }
    }

    /*
    ==================================================
                    CONSTRUCTORS
    ==================================================
    */


    Fraction::Fraction(int a, int b){
        if(b == 0){
            throw std::invalid_argument("dividing by zero exeption");
        }else{
            this->numerator = a;
            this->denominator = b;
        }

    }

    Fraction::Fraction(float f){
        Fraction newF = this->transfer(f);
        int b = newF.getDenominator();
        int a = newF.getNumerator();
        if(b == 0){
            throw std::invalid_argument("dividing by zero exeption");
        }else{
            this->numerator = a;
            this->denominator = b;
        } 
    }

    Fraction::Fraction(){
        this->numerator = 1;
        this->denominator = 1;
    }
    

    /*
    ==================================================
                        operators
    ==================================================
    */

    Fraction Fraction::operator+(const Fraction& other) const{
        Fraction result;
        int lcm_value = lcm(this->denominator, other.denominator);
        int num1 = this->numerator * (lcm_value / this->denominator);
        int num2 = other.numerator * (lcm_value / other.denominator);
        result.numerator = num1 + num2;
        result.denominator = lcm_value;

        int numerator;
        if ( __builtin_sadd_overflow(num1 , num2, &numerator) && !__builtin_mul_overflow(result.denominator , 2, &numerator)){
            throw std::overflow_error("Overflow error: result is too large");
        }

        if ( !__builtin_sadd_overflow(num1 , num2, &numerator) && __builtin_mul_overflow(result.denominator , 2, &numerator)){
            throw std::overflow_error("Overflow error: result is too large");
        }


        return this->reduction(result);
    }


    std::ostream& operator<<(std::ostream& os, Fraction& F) {
        Fraction F2(F.getNumerator(), F.getDenominator());
        F2 = F2.reduction(F2);
        os << F2.getNumerator() << "/" << F2.getDenominator();
        return os;
    }

    // input operator
    std::istream& operator>>(std::istream& input, Fraction& F) {
        char c;
        int num , den;
         
        input >> num >> den ;
        
        if (input && den != 0) {
        F.SetNumerator(num);
        F.SetDenominator(den);
        }   
        else {
            throw runtime_error("Bad_in");
        }
        return input;
    }

    Fraction Fraction::operator-(const Fraction& other) const{
        Fraction result;// 1/2, 2/4
        int lcm_value = lcm(this->denominator, other.denominator);// lcm = 4
        int num1 = this->numerator * (lcm_value / this->denominator);// 1 * 2
        int num2 = other.numerator * (lcm_value / other.denominator);// 2 * 1
        result.numerator = num1 - num2;// 2 - 2 = 0
        result.denominator = lcm_value;// 0/4

         int numerator;
        if ( __builtin_ssub_overflow(num1 , num2, &numerator) && !__builtin_mul_overflow(result.denominator , 2, &numerator)){
            throw std::overflow_error("Overflow error: result is too large");
        }

        if ( !__builtin_sadd_overflow(num1 , num2, &numerator) && __builtin_mul_overflow(result.denominator , 2, &numerator)){
            throw std::overflow_error("Overflow error: result is too large");
        }


        return this->reduction(result);
    }


    Fraction Fraction::operator*(const Fraction& other) const{
        
        Fraction result;
        result.numerator = this->numerator * other.numerator;
        result.denominator = this->denominator * other.denominator;

        int numerator;
        if ( __builtin_mul_overflow(this->denominator , other.numerator, &numerator) && !__builtin_mul_overflow(this->numerator , other.denominator, &numerator)){
            throw std::overflow_error("Overflow error: result is too large");
        }

        if ( !__builtin_mul_overflow(this->denominator , other.numerator, &numerator) && __builtin_mul_overflow(this->numerator , other.denominator, &numerator)){
            throw std::overflow_error("Overflow error: result is too large");
        }


        return this->reduction(result);
    }

    Fraction Fraction::operator/(const Fraction& other) const{
        Fraction result;

        result.denominator = this->denominator * other.numerator;
        result.numerator = this->numerator * other.denominator;
        if(other.numerator == 0){
            throw std::runtime_error("dividing by zero exeption");
        }

        int numerator;
        if ( __builtin_mul_overflow(this->denominator , other.numerator, &numerator) && !__builtin_mul_overflow(this->numerator , other.denominator, &numerator)){
            throw std::overflow_error("Overflow error: result is too large");
        }

        if ( !__builtin_mul_overflow(this->denominator , other.numerator, &numerator) && __builtin_mul_overflow(this->numerator , other.denominator, &numerator)){
            throw std::overflow_error("Overflow error: result is too large");
        }
        return this->reduction(result);
    }
 
    bool Fraction::operator==(const Fraction& other) const{
        Fraction f1(this->numerator, this->denominator);
        Fraction f2(other.numerator, other.denominator);
        f1 = f1.reduction(f1);
        f2 = f2.reduction(f2);
        return (f1.denominator == f2.denominator && f1.numerator == f2.numerator);
    }

    bool Fraction::operator>(const Fraction& other) const{
        return (double(this->numerator)/this->denominator > double(other.numerator)/other.denominator);
    }

    bool Fraction::operator>=(const Fraction& other) const{
        return (double(this->numerator)/this->denominator >= double(other.numerator)/other.denominator);
    }

    bool Fraction::operator<(const Fraction& other) const{
        return (double(this->numerator)/this->denominator < double(other.numerator)/other.denominator);
    }

    bool Fraction::operator<=(const Fraction& other) const{
        return (double(this->numerator)/this->denominator <= double(other.numerator)/other.denominator);
    }

    Fraction Fraction::operator++(){
        this->numerator += this->denominator;
        this->reduction(*this);
        return *this;
    }

    Fraction Fraction::operator--(){
        this->numerator -= this->denominator;
        this->reduction(*this);
        return *this;
    }

    Fraction Fraction::operator ++(int){
        Fraction temp = *this;
        this->numerator += this->denominator;
        this->reduction(*this);
        return temp;
    }

    Fraction Fraction::operator --(int){
        Fraction temp = *this;
        this->numerator -= this->denominator;
        this->reduction(*this);
        return temp;
    }

    Fraction operator+(const float& left, const Fraction& right){
        Fraction fraction = right;
        return fraction + left;
    }

    Fraction operator-(const float& left, const Fraction& right){
        Fraction fraction = right;
        fraction.SetNumerator(fraction.getNumerator()*-1);
        return fraction + left;
    }

    Fraction operator*(const float& left, const Fraction& right){
        Fraction fraction = right;
        return fraction * left;
    }

    Fraction operator/(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f / right_f; 
    }

    bool operator==(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f == right_f; 
    }

    bool operator>(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f > right_f; 
    }

    bool operator>=(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f >= right_f; 
    }

    bool operator<(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f < right_f; 
    }

    bool operator<=(const float& left, const Fraction& right){
        Fraction left_f;
        Fraction right_f = right;
        left_f = left_f.transfer(left);
        return left_f <= right_f; 
    }

    int Fraction::gcd(int a, int b) const{
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    int Fraction::lcm(int a, int b) const{
        return (a * b) / gcd(a, b);
    }

        
    Fraction Fraction::transfer(float f) const{
        // Multiply the float by 1000 to convert the decimal part to an integer
        int numerator = static_cast<int>(std::round(f * 1000));

        // The denominator is 1000
        int denominator = 1000;

        // Reduce the fraction and return it
        Fraction f2(numerator, denominator);
        return this->reduction(f2);
    }

    // Reduces the fraction
    // minus will always appear in the denominator
    Fraction Fraction::reduction(Fraction& f) const{
        Fraction result;
        int gcd = this->gcd(f.numerator, f.denominator);
        result.denominator = f.denominator/gcd;
        result.numerator = f.numerator/gcd;

        //On the one hand, you have to maintain an accuracy of three points after the point, 
        //on the other hand, you can also give huge numbers and check for errors
        if(result.denominator > 1000000000 || result.numerator > 1000000000)
            return result;


        // To ensure accuracy of three points after the zero
        if(result.denominator > 1000){
            double smaller = (double)result.numerator / result.denominator;
            Fraction f2 = this->transfer(smaller);
            return f2;
        }
                
        if(result.denominator < 0 && result.numerator > 0){
            result.denominator *= -1;
            result.numerator *= -1;
        }

        return result;
    }

}









    
