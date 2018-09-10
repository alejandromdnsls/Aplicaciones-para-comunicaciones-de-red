/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica1;

import javax.swing.JFileChooser;
import java.net.*;
import java.io.*;

/**
 *
 * @author alejandroms
 */
public class ClienteArchivo {
    File[] file;
    int tam_buffer;
    
    public ClienteArchivo(File[] f, String buffer){
        this.file = f;
        this.tam_buffer = Integer.parseInt(buffer);
    }
    
    public void enviaArchivos(){
        try{
            Socket cl = new Socket("127.0.0.1", 7000);
            DataOutputStream dos = new DataOutputStream(cl.getOutputStream());
            DataInputStream dis = null;            
            int num_archivos = file.length;
            System.out.println("Número de archivos: " + num_archivos);
            System.out.println("Tamaño de buffer: " + tam_buffer);
            dos.writeInt(num_archivos);
            dos.writeInt(tam_buffer);
            dos.flush();
            String archivo = "";
            String nombre = "";
            long tam = 0;
            int i = 0;            
            while(i < num_archivos){ 
                archivo = file[i].getAbsolutePath();
                nombre = file[i].getName();
                tam = file[i].length();
                System.out.println("Archivo: " + file[i].getName());
                System.out.println("Tamaño Archivo: " + tam);
                dis = new DataInputStream(new FileInputStream(archivo));                    
                dos.writeUTF(nombre);
                dos.writeLong(tam);
                dos.flush();                            
                byte[] b = new byte[tam_buffer];
                long enviados = 0;
                int porcentaje, n;
                while(enviados < tam){
                    n = dis.read(b);                                              
                    dos.write(b, 0, n);
                    dos.flush();
                    enviados = enviados + n;                        
                    porcentaje = (int)(enviados * 100 / tam);
                    System.out.print("Enviado: " + porcentaje + "%\r");
                }
                i++;
                System.out.print("\n\nArchivo enviado\n");
            }
            dos.close();
            dis.close();
            cl.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
       
}