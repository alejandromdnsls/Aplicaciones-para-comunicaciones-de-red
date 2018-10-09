package multicast;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class SMulticast {
    public static void main(String[] args) {
        InetAddress gpo = null;
        try{
            MulticastSocket s = new MulticastSocket(9876);
            s.setReuseAddress(true);//otro aplicaciones pueden utilizar el 
            s.setTimeToLive(1);//solo un salto
            String msj = "hola";
            byte[] b = msj.getBytes();
            gpo = InetAddress.getByName("230.0.0.1");
            s.joinGroup(gpo);
            for(;;){
                DatagramPacket p = new DatagramPacket(b, b.length, gpo, 9999);
                s.send(p);
                System.out.println("Enviando mensaje" + msj + "con un TTL = " + s.getTimeToLive());
                try{
                    Thread.sleep(3000); //3 segundos                    
                }catch(InterruptedException ie){
                    ie.printStackTrace();
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }    
}
