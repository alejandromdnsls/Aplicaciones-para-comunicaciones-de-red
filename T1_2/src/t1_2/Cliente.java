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
public class Cliente {
    public static void main(String[] args){
        try{
            BufferedReader br1 = new BufferedReader(new InputStreamReader(System.in));
            System.out.printf("Escriba la dirección del servidor: ");
            String host = br1.readLine();
            System.out.printf("\n\nEscriba el puerto:");
            int pto = Integer.parseInt(br1.readLine());
            Socket cl = new Socket(host, pto);
            BufferedReader br2 = new BufferedReader(new InputStreamReader(cl.getInputStream()));
            String mensaje = br2.readLine();
            System.out.println("Recibimos un mensaje desde el servidor");
            System.out.println("Mensaje:" + mensaje);
            String menviado = "Hola desde el Cliente";
            PrintWriter pw = new PrintWriter(new OutputStreamWriter(cl.getOutputStream()));
            pw.println(menviado);
            pw.flush();
            pw.close();
            br1.close();
            br2.close();
            cl.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }   
}