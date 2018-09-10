/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t1_4;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 *
 * @author alejandroms
 */
public class CHolaD {
    public static void main(String[] args){
        try{
            //Creamos un socket de datagrama y lo liga a algún puerto de la computadora lcal
            DatagramSocket cl = new DatagramSocket();
            System.out.println("Cliente iniciado, escriba un mensaje de saludo: ");
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String mensaje = br.readLine();
            byte[] b = mensaje.getBytes();
            String dst = "127.0.0.1";
            int pto = 2000;
            DatagramPacket p = new DatagramPacket(b, b.length, InetAddress.getByName(dst), pto);
            cl.send(p);
            p = new DatagramPacket(new byte[2000], 2000);
            cl.receive(p);
            String msj = new String(p.getData(), 0, p.getLength());        
            System.out.println("Mensaje de vuelta: " + msj);
            cl.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
