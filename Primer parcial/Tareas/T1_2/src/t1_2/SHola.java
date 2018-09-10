/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t1_2;

import java.net.*;
import java.io.*;
/**
 *
 * @author alejandroms
 */
public class SHola {
    public static void main(String[] args){
        try{
            ServerSocket s= new ServerSocket(1234);
            System.out.println("Esperando cliente...");
            for(;;){
                Socket cl = s.accept(); //bloqueo
                System.out.println("Conexión establecida desde" + cl.getInetAddress() + ":" +
                        cl.getPort());
                String mensaje = "Hola mundo";
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(cl.getOutputStream()));
                pw.println(mensaje);
                pw.flush();
                BufferedReader br = new BufferedReader(new InputStreamReader(cl.getInputStream()));
                String mrecibido = br.readLine();
                System.out.println("Recibimos un mensaje desde el cliente");
                System.out.println("Mensaje: " + mrecibido);
                pw.close();
                br.close();                              
                cl.close();
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
