/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package p2_1;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.NetworkInterface;
import java.net.UnknownHostException;

public class ServidorMulticast {
    public static void main(String[] args) {
        InetAddress gpo = null;
        try{
            MulticastSocket s = new MulticastSocket(4000);
            System.out.println("Servidor escuchando puerto " + s.getLocalPort());
            s.setReuseAddress(true);          
            try{
                gpo = InetAddress.getByName("230.0.0.1");                
            }catch(UnknownHostException u){
                System.err.println("Dirección no válida");
            }            
            NetworkInterface ni = NetworkInterface.getByName("en1");
            s.setNetworkInterface(ni);            
            s.joinGroup(gpo);
            for(;;){
               DatagramPacket p = new DatagramPacket(new byte[10], 10);
               s.receive(p); 
               String msj = new String(p.getData());
               System.out.println("Datagrama recibido... " + msj);
               System.out.println("Serivdor descubierto: " + p.getAddress() + ":" + p.getPort());                
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }    
}

