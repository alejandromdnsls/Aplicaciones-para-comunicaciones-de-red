/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t1_4;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 *
 * @author alejandroms
 */
public class SHolaD {
    public static void main(String[] args){
        try{
            //Creamos un socket de datagrama y lo ligamos a un puerto
            DatagramSocket s = new DatagramSocket(2000);
            System.out.println("Servidor iniciado, esperando cliente...");
            for(;;){
                //Se crea DatagramPacket para recibir paquete de longitug 2000                
                DatagramPacket p = new DatagramPacket(new byte[512], 512);               
                s.receive(p);                               
                System.out.println("Datagrama recibido desde: " + p.getAddress() + ":" + p.getPort());                              
                String msj = new String(p.getData(), 0, p.getLength());
                System.out.println(msj.length());
                System.out.println("Con el mensaje: " + msj);
                //Se crea un DatagramPacket para hacer un response con el mismo mensaje                
                byte[] b = msj.getBytes();
                DatagramPacket p1 = new DatagramPacket(b, b.length, p.getAddress(), p.getPort());
                s.send(p1);                
            }            
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    
}
