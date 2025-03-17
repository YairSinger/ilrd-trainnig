#include <iostream>

class RecomandationLogic
{   
public:
    PortfolioRecomandation getPortfolioRecomandation();
private:
   
};


class Investor
{
public:
    explicit Investor(std::string name, int age, int dependents, float savingsRate, int invesmentHorizon, float incomeStability, float confidenceInInvesting, float strategyConsistency, float riskTolerance);

    PortfolioRecomandation getPortfolioRecomandation();



private:
    std::string name;
    int age;                            //years
    int dependents;                     //number of dependents
    float savingsRate;                  //savings per year [%]
    int invesmentHorizon;               //years
    float incomeStability;              //precent 0% means no stability, 100% means full stability
    float confidenceInInvesting;        //precent 0% means no confidence, 100% means full confidence
    float strategyConsistency;          //precent 0% means no consistency, 100% means full consistency
    float riskTolerance;                //precent 0% means no tolerance, 100% means full tolerance
    long totalNetWorth;                
    int numOfMonthsSavings;             // (1-savingsRate[%]) / totalNetWorth
    float creditScore;                  //precent 0% means poor credit score, 100% means good credit score 
    PortfolioRecomandation portfolioRecomandation;
};

enum ELeverageLimatator
{
    LEVERAGE_LIMITATOR_INCOME = 0,
    LEVERAGE_LIMITATOR_EQUITY ,
    LEVERAGE_LIMITATOR_CREDIT
};


class PortfolioRecomandation
{
public:
   PortfolioRecomandation(float averageRiskLevel, float maxLeveragePrecentage, ELeverageLimatator leverageLimitFactore);
   void printPortfolioRecomandation();
private:
    float averageRiskLevel;
    float maxLevergePrecentage;
    ELeverageLimatator leverageLimitFactore;    
};

