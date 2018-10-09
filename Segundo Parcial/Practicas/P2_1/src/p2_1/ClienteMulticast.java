package p2_1;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.NetworkInterface;
import java.net.UnknownHostException;

/**
 *
 * @author alejandroms
 */
public class ClienteMulticast {
    public static void main(String[] args) {
        InetAddress gpo = null;
        try{
            MulticastSocket cl = new MulticastSocket(4000);
            System.out.println("Cliente conectado al puerto " + cl.getLocalPort());
            cl.setReuseAddress(true);
            try{
                gpo = InetAddress.getByName("230.1.1.1");                
            }catch(UnknownHostException u){
                System.err.println("Dirección no válida");
            }
            NetworkInterface ni = NetworkInterface.getByName("en1");
            cl.setNetworkInterface(ni);
            cl.joinGroup(gpo);
            System.out.println("Unido al grupo");
           
            for(;;){                
                try{
                    Thread.sleep(2000); //3 segundos                    
                }catch(InterruptedException ie){
                    ie.printStackTrace();
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }    
}
