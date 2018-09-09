/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t3_1;

/**
 *
 * @author alejandroms
 */
import java.net.*;
import java.io.*;

public class ServidorArchivo {
    public static void main(String[]args){
        try{
            ServerSocket s = new ServerSocket(7000);
            //Iniciamos el ciclo infinito y esperamos una conexión
            for(;;){
                Socket cl = s.accept();
                System.out.println("Conexión establecida desde: " + 
                        cl.getInetAddress() + ":" + cl.getPort());
                //Se define un flujo de nivel de bits de entrada ligado al socket
                DataInputStream dis = new DataInputStream(cl.getInputStream());
                DataOutputStream dos = null;
                //Se leen los datos principales del archivo               
                int num_archivos = dis.readInt();
                int contador = 0;
                do{                   
                    int tam_buffer = 1024;
                    byte[] b = new byte[tam_buffer];                    
                    String nombre = dis.readUTF();
                    System.out.println("Recibimos el archivo: " + nombre);
                    long tam = dis.readLong();
                    System.out.println("Tamaño archivo: " + tam);
                    //Se crea un flujo para escribir el archivo de salida                     
                    dos = new DataOutputStream(new FileOutputStream(nombre));
                    //Se preparan los datos para recibir los paquetes de datos del archivo
                    long recibidos = 0;
                    int n, porcentaje;
                    while(recibidos < tam){
                        if(tam - recibidos < tam_buffer){                            
                            tam_buffer = (int)(tam - recibidos);                            
                            b = new byte[tam_buffer];                            
                        }
                        n = dis.read(b);                                            
                        dos.write(b, 0, n);
                        dos.flush();
                        recibidos = recibidos + n;                        
                        porcentaje = (int)(recibidos * 100 / tam);
                        System.out.print("Recibido: " + porcentaje + "%\r");
                    }
                    System.out.print("\n\nArchivo recibido.\n");
                    contador++;
                }while(contador < num_archivos);                
                dos.close();
                dis.close();
                cl.close();
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }   
}