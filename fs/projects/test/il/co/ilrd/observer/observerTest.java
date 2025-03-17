package il.co.ilrd.observer;

import org.junit.Test;

import java.util.*;

 public class observerTest {


   class NewsPaper{
      private String paperName;
      private Dispatcher<String> dispatcher = new Dispatcher<>();
      private String state = new String("first publish");

      public NewsPaper(String paperName) {
          this.paperName = paperName;
      }

      public void subscribe(Callback<String> callback){
          dispatcher.subscribe(callback);
      }
      public void unsubscribe(Callback<String> callback){
          dispatcher.unsubscribe(callback);
      }

      public void setState(String state) {
          this.state = state;
          dispatcher.updateAll( paperName +  "new state: " + this.state);
      }
  }

   class NPReader{
      private Map<NewsPaper,Callback<String>> subscriptions = new HashMap<>();

      public void subscribe(NewsPaper paper){
          Callback<String> callback= new Callback<>((a)-> {System.out.println(a); return null;},
                  (a)-> {System.out.println("removed"); return null;});
          paper.subscribe(callback);
          subscriptions.put(paper, callback);
      }

      public void unsubscribe(){
          for (NewsPaper newsPaper : subscriptions.keySet()) {
             newsPaper.unsubscribe(subscriptions.get(newsPaper));
          }
      }
  }

   class Portfolio{

      private volatile Long portfolioTotalValue;
      private final List<String> portfolioList;

      private Dispatcher<String> compObservers;
      private Dispatcher<Long> valueObservers;

      public void addSubs(Callback<String> companies, Callback<Long> value) {
          if(companies != null) {
              compObservers.subscribe(companies);
          }
          if(value != null) {
              valueObservers.subscribe(value);
          }
      }


      public Portfolio(Long netMarketValue, List<String> portfolioList) {
          this.portfolioTotalValue = netMarketValue;
          this.portfolioList = portfolioList;
          compObservers = new Dispatcher<>();
          valueObservers = new Dispatcher<>();

      }

      public void addCompany(String companyName, Long curMarketCap){
          portfolioList.add(companyName);
          portfolioTotalValue += curMarketCap;
          compObservers.updateAll(companyName + " were added to out portfolio");
          valueObservers.updateAll(portfolioTotalValue);
      }

      public void updatePriceChange(String companyName, Long deltaInPrice ){
          if(portfolioList.contains(companyName)){
              portfolioTotalValue =  portfolioTotalValue.longValue() + deltaInPrice;
              valueObservers.updateAll(portfolioTotalValue);
          }
      }

      public void updateMergedCompany(String companyName){
          portfolioList.remove(companyName);
          compObservers.updateAll(companyName + " was removed from out portfolio");
      }
  }
   class Broker{

      Map<Dashboard,Portfolio> list;


       public Broker(Dashboard dash, Portfolio portfolio) {
           list = new HashMap<>();
           list.put(Objects.requireNonNull(dash),Objects.requireNonNull(portfolio));
           portfolio.addSubs(dash.callback,dash.getCallbackLong());
       }

       public void addDashboard(Dashboard dash, Portfolio portfolio){
           list.put(Objects.requireNonNull(dash),Objects.requireNonNull(portfolio));
           portfolio.addSubs(dash.callback,dash.getCallbackLong());
       }
       public void addCompany(Dashboard dash, String companyName, Long curMarketCap) {
          if(dueDiligenceChack(companyName,curMarketCap)){
              list.get(dash).addCompany(companyName,curMarketCap);
          }
      }

       public void updatePriceChange(Dashboard dash, String companyName, Long deltaInPrice ) {
           if(dueDiligenceChack(companyName)){
               list.get(dash).updatePriceChange(companyName, deltaInPrice);
           }
      }

       public void updateMergedCompany(Dashboard dash, String companyName){
           if(dueDiligenceChack(companyName)){
               list.get(dash).updateMergedCompany(companyName);
           }
       }


      private boolean dueDiligenceChack(String companyName){
          return true;
      }
       private boolean dueDiligenceChack(Long curMarketCap){
           return true;
       }
       private boolean dueDiligenceChack(String companyName, Long curMarketCap){
           return true;
       }
  }
  class Dashboard{
      private Callback<String> callback;
      private Callback<Long> callbackLong;

      public Callback<String> getCallbackString() {
          return callback;
      }

      public Callback<Long> getCallbackLong() {
          return callbackLong;
      }

      public Dashboard(boolean callback, boolean callbackLong) {
          if (callback){
              this.callback = new Callback<>((a)-> {System.out.println(a); return null;},
                      (a)-> {System.out.println("removed"); return null;});
          }
          if (callbackLong){
             this.callbackLong= new Callback<>((a)-> {System.out.println(a); return null;},
                      (a)-> {System.out.println("removed"); return null;});
          }

      }
  }

  @Test
  public void MVC(){
       List list = new ArrayList<String>();
       list.add("fjfjf");
       Portfolio portfolio  = new Portfolio(1000L, list);
       Dashboard onlyVals = new Dashboard(false,true);
       Dashboard allDash = new Dashboard(true,true);
       Broker broker = new Broker(onlyVals,portfolio);
       broker.addDashboard(allDash,portfolio);
       broker.addCompany(onlyVals,"Intel", 12345L);
       broker.updatePriceChange(onlyVals,"Intel",-12130L);
       broker.updateMergedCompany(allDash, "Intel");
       Dashboard onlyCompaniesDash = new Dashboard(true, false);
       Thread thread = new Thread(()->{broker.addDashboard(onlyCompaniesDash,portfolio);});
       Thread thread2 = new Thread(()->{broker.addCompany(onlyVals,"Apple", 10000000L); ;});

      thread.start();
      thread2.start();

  }
    @Test
    public void NewsTest(){
     NewsPaper maariv = new NewsPaper("Maariv");
     NewsPaper yediot = new NewsPaper("Yediot");

     NPReader firstReader = new NPReader();
     NPReader secReader = new NPReader();

     firstReader.subscribe(maariv);
     maariv.setState(" 7.10.23 a war started!");
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        maariv.setState(" starting winning");
        System.out.println("reader1 unsubscribed");
        firstReader.unsubscribe();
        maariv.setState(" 1.4.23 war ended!");

        firstReader.subscribe(maariv);
        secReader.subscribe(maariv);
        maariv.setState("Nobel prise ...");

        firstReader.subscribe(yediot);
        yediot.setState("wejnr");
        maariv.setState("sfjnbf");
        firstReader.unsubscribe();
        maariv.setState("sfjnbf");
        yediot.setState("wejnr");


    }


}