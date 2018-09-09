/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t3_1;

import javax.swing.JFileChooser;
import java.net.*;
import java.io.*;
import java.util.ArrayList;

/**
 *
 * @author alejandroms
 */
public class ClienteArchivo {
    public static void main(String[] args){
        try{
            //Se define el socket
            Socket cl = new Socket("127.0.0.1", 7000);
            //Se utiliza JFileChooser() para elegir un archivo
            JFileChooser jf = new JFileChooser();
            jf.setMultiSelectionEnabled(true);
            int r = jf.showOpenDialog(null);
            //Se obtienen sus datos
            if(r == JFileChooser.APPROVE_OPTION){
                File[] file = jf.getSelectedFiles(); //Manejador
                //Se definen dos flujos orientados a bytes, uno se usa para leer el archivo
                // y otro para enviar los datos por el socket
                DataOutputStream dos = new DataOutputStream(cl.getOutputStream());
                DataInputStream dis = null;
                int i = 0;
                int num_archivos = file.length;
                dos.writeInt(num_archivos);
                dos.flush();
                String archivo = "";
                String nombre = "";
                long tam = 0;
                System.out.println("Núm archivos: " + file.length);
                while(i < file.length){ 
                    archivo = file[i].getAbsolutePath();
                    nombre = file[i].getName();
                    tam = file[i].length();
                    System.out.println("Archivo: " + file[i].getName());
                    System.out.println("Tamaño Archivo: " + tam);
                    dis = new DataInputStream(new FileInputStream(archivo));                    
                    dos.writeUTF(nombre);
                    dos.writeLong(tam);
                    dos.flush();
                    //byte[] b = new byte[1024];
                    int tam_buffer = 1024;
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
            }    
        }catch(Exception e){
            e.printStackTrace();
        }
    }    
}
