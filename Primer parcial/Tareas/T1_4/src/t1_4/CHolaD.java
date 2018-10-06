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
            final int MAXLEN = 512;
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
            //Se crea un DatagramPacket para recibir el mensaje
            DatagramPacket p1 = new DatagramPacket(new byte[MAXLEN], MAXLEN);
            cl.receive(p1);
            String msj = new String(p.getData(), 0, p.getLength());
            System.out.println("Mensaje devuelto: " + msj);
            /*
            int tam = b.length;
            int enviados = 0;
            double numveces = tam * 100 / MAXLEN;
            while(enviados < tam){                
                if(numveces > 1){                    
                    DatagramPacket p3 = new DatagramPacket(b, b.length , InetAddress.getByName(dst), pto);
                    byte[] b_aux = null;
                    for(int i = 0; i < MAXLEN; i++){
                        b_aux[i] = b[i];                        
                    }
                    
                }
                else if(numveces <= 1){
                    
                }
                //512 100
                //612 
            }*/
            cl.close();           
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
