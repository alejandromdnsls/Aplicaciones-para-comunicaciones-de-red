/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package multicast;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.NetworkInterface;
import java.net.UnknownHostException;

/**
 *
 * @author alejandroms
 */
public class CMulticast {
    public static void main(String[] args) {
        InetAddress gpo = null;
        try{
            MulticastSocket cl = new MulticastSocket(9999);
            System.out.println("Cliente escuchando puerto " + cl.getLocalPort());
            cl.setReuseAddress(true);
            try{
                gpo = InetAddress.getByName("228.1.1.1");                
            }catch(UnknownHostException u){
                System.err.println("Dirección no válida");
            }
            NetworkInterface ni = NetworkInterface.getByName("en1");
            cl.setNetworkInterface(ni);
            cl.joinGroup(gpo);
            System.out.println("Unido al grupo");
            int i = 0;
            for(;;){
                DatagramPacket p = new DatagramPacket(new byte[512], 512);
                cl.receive(p);
                String msj = new String(p.getData(), 0, p.getLength());                               
                System.out.println("Datagrama recibido... " + msj);
                System.out.println("Servidor descubierto: " + p.getAddress() + ":" + p.getPort());
                cl.setTimeToLive(1);//solo un salto              
                String msj2 = "hola desde cliente " + i;
                byte[] b = msj2.getBytes();
                DatagramPacket p2 = new DatagramPacket(b, b.length, gpo, 9999);
                cl.send(p2);
                System.out.println("\tEnviando mensaje " + msj2 + " con un TTL = " + cl.getTimeToLive());
                i++;
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

//Tarea: Cliente inyectar tramas al canal