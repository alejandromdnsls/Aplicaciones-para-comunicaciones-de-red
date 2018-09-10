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
                DatagramPacket p = new DatagramPacket(new byte[2000], 2000);
                s.receive(p);                
                byte[] b = p.getData();
                int tam = p.getLength();
                InetAddress host = p.getAddress();
                int port = p.getPort();
                System.out.println("Datagrama recibido desde: " + host + ":" + port);                              
                String msj = new String(b, 0, tam);
                System.out.println("Con el mensaje: " + msj);
                b = msj.getBytes();
                p = new DatagramPacket(b, b.length, host, port);
                s.send(p);                
            }            
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    
}
