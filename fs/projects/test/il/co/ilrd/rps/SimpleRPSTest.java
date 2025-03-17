package il.co.ilrd.rps;

import org.junit.Test;

public class SimpleRPSTest {

    @Test
    public void handleRequest() throws InterruptedException {
        RPS rps = new RPS();
        rps.handleRequest("registerCompany-Intel ltd");
        rps.handleRequest("registerProduct-i7 gen17 processor");
        rps.handleRequest("registerIOT-i7 gen17 1234567");
        rps.handleRequest("updateIOT-i7 gen17 1234567@turned on");
        rps.handleRequest("updateIOT-i7 gen17 1234567@running");


        Thread.sleep(2000);
    }
}