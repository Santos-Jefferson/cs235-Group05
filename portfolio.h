#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "handletrans.h"
#include "queue.h"
#include <iostream>

#include <string>      // for STRING
#include <cassert>     // for ASSERT

using namespace std;

class Portfolio
{
  private:
   Queue<HandleTrans> holdings;
   Dollars proceeds;
   Queue<HandleTrans> history;

  public:
   //default constructor
  Portfolio()
  {
     proceeds=0;
  };

   //destructor
  ~Portfolio(){};

   //purchase a stock, overloaded
   void buy(HandleTrans trans)
   {
      holdings.push(trans);
      return;
   };

   void buy(int vol, Dollars pr)
   {
      HandleTrans newHandleTrans;
      newHandleTrans.volume=vol;
      newHandleTrans.price=pr;
      holdings.push(newHandleTrans);
   };

   //sell a stock
   Dollars sell(int volTotal, Dollars pr)
   {
      Dollars profit=0;
      int vol=volTotal;
      //cerr << "Before sell loop" << endl;
      while(vol!=0)
      {
         if(holdings.front().volume>vol)
         {
            //cout<<"We are starting to subtract from last buy"<<endl;
            int currVol=holdings.front().volume;
            int newVol=currVol-vol;
            holdings.front().volume=newVol;
            profit=(pr-holdings.front().price)*vol;
            HandleTrans trans;
            trans.profit=(pr-holdings.front().price)*vol;
            trans.volume=vol;
            trans.price=pr;
            history.push(trans);
            vol=0;
            proceeds=proceeds+profit;
         }
         else if(holdings.front().volume==vol)
         {
            //cerr << "ELSE IF - SELL" << endl;
//            cerr << holdings.front().volume << endl;
            try {
               profit=(pr-holdings.front().price)*vol;
               holdings.pop();
               HandleTrans trans;
               trans.profit=profit;
               trans.volume=vol;
               trans.price=pr;
               history.push(trans);
               proceeds=proceeds+profit;
               vol=0;
            }
            catch(string message)
            {
               cout<<message;
            }
         }
         else
         {
            profit=((pr-holdings.front().price)*holdings.front().volume);
           
            int oldVol=holdings.front().volume;
           
            holdings.pop();
            HandleTrans trans;
            trans.profit=profit;
            trans.price=pr;
            vol=vol-oldVol;
            trans.volume=oldVol;
            history.push(trans);
            proceeds=proceeds+profit;
            // cout<<"We made it to the end of the first buy"<<endl;
         }
      }
      return profit;
   };
               
   //getters
   Queue<HandleTrans> getPortfolio()
   {
      return holdings;
   };
   
   Dollars getProceeds()
   {
      return proceeds;
   };

   Queue<HandleTrans> getHistory()
   {
      return history;
   };

   //display
   void display()
   {
      Queue<HandleTrans> tmpHold=holdings;
      if(!holdings.empty())
         cout<<"Currently held:"<<endl;
      while(!tmpHold.empty())
      {
         cout<<"\tBought "<<tmpHold.front().volume
             <<" shares at "<<tmpHold.front().price<<endl;
         tmpHold.pop();
      }
      Queue<HandleTrans> tmpHist=history;
      if(!history.empty())
         cout<<"Sell History:"<<endl;
      while(!tmpHist.empty())
      {
         cout<<"\tSold "<<tmpHist.front().volume
             <<" shares at "<<tmpHist.front().price
             <<" for a profit of "<<tmpHist.front().profit<<endl;
         tmpHist.pop();
      }
      cout<<"Proceeds: "<<proceeds<<endl;
   };
};
   
#endif