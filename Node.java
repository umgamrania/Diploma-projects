// import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
// import java.io.InputStreamReader;
// import java.io.OutputStream;
import java.net.*;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;

// HELLO WORLD!

import javax.annotation.processing.SupportedOptions;

class MulticastClient {
    String groupAddress = "224.0.0.1";
    int port;
    MulticastSocket socket;
    static HashMap<String, String> onlineClients;

    public static String getNthIP(int n){
        Set<String> keySet = onlineClients.keySet();
        String[] keysArray = keySet.toArray(new String[0]);

        if (n >= 0 && n < keysArray.length) {
            String nthKey = keysArray[n];
            return nthKey;
        } else {
            System.out.println("Invalid n");
        }
        return "";
    }

    MulticastClient()
    {
        this(8888);
        this.port = 8888;
    }
    MulticastClient(int p)
    {
        try
        {
            socket = new MulticastSocket(p);
            this.port = p;
            MulticastClient.onlineClients = new HashMap<>();
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
        this.port = p;
    }

    public int listen()
    {
        try
        {

            InetAddress group = InetAddress.getByName(groupAddress);
            socket.joinGroup(group);

            byte[] receiveData;

            System.out.println("Listening for multicast messages...");

            while (true) {
                receiveData = new byte[1024];
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                socket.receive(receivePacket);

                String message = new String(receivePacket.getData()).trim();
                parseMessage(message);
                // ListenThread.getList();

            }
        }
        catch(Exception e)
        {
            System.out.println(e);
        }

        return 0;
    }

    private void parseMessage(String msg)
    {
        String message[] = msg.split(",");

        if(message[0].equals("ping")){
            if(!onlineClients.containsKey(message[1]) && !message[2].equals(Node.username)){
                MulticastClient.onlineClients.put(message[1], message[2]);
                ListenThread.getList();
            }
        }
        else if(message[0].equals("remove")){
            if(onlineClients.containsKey(message[1])){
                MulticastClient.onlineClients.remove(message[1]);
                ListenThread.getList();
            }
        }
    }
}

class MulticastServer {
    private static String groupAddress = "224.0.0.1";
    private MulticastSocket socket;
    private int port;

    MulticastServer(){
        this(8888);
        this.port = 8888;
    }

    MulticastServer(int port){
        this.port = port;
        try{
            this.socket = new MulticastSocket(port);
        }
        catch(Exception e){
            System.out.println("Error while creating MulticastSocket: " + e.getMessage());
        }
    }

    public void closeSocket(){
        this.socket.close();
    }

    public int sendMulticastMessage(String message){
        byte[] sendData = message.getBytes();

        try{
            InetAddress group = InetAddress.getByName(MulticastServer.groupAddress);
            DatagramPacket packet = new DatagramPacket(sendData, sendData.length, group, port);
            socket.send(packet);
        }catch(UnknownHostException e){
            System.out.println("Unkown Host exception: " + e.getMessage());
            return -1;
        }
        catch(Exception e){
            System.out.println("Error while sending message: " + e.getStackTrace());
            return -1;
        }

        return 1;
    }

    public String getIp(){
        try {
            // Get the local host address
            InetAddress localHost = InetAddress.getLocalHost();
            String ipAddress = localHost.getHostAddress();
            return ipAddress;
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
        return "CANNOT_GET_IP";
    }
}

class PingThread extends Thread{
    @Override
    public void run() {
        MulticastServer server = new MulticastServer();

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            // Code to execute when the program exits
            System.out.println("Sending remove msg");
            server.sendMulticastMessage("remove," + Node.IP + "," + Node.username);
        }));

        while (true) {
            server.sendMulticastMessage("ping," + Node.IP + "," + Node.username);

            try{
                Thread.sleep(1000);
            }catch(Exception e){}
        }
    }
}

class ListenThread extends Thread{
    private static MulticastClient client;

    @Override
    public void run(){
        client = new MulticastClient();
        client.listen();
    }

    public static void getList(){
        System.out.println("\033[2J\033[HAvailable Nodes: \n");

        int counter = 0;
        for(String key : MulticastClient.onlineClients.keySet()){
            System.out.println(counter + ") " + MulticastClient.onlineClients.get(key) + " - " + key);
            counter++;
        }

        System.out.print("\nEnter node no. to chat with: ");
    }
}

class BaseThread extends Thread{
    public static boolean isRequestPresent = false;
    public static String requestIp;
    public static String requestName;
    public static boolean isChatActive = false;
}

class ConnectListen extends BaseThread{
    @Override
    public void run() {
        try{
            ServerSocket serverSocket = new ServerSocket(1234);
            
            while(true){
                Socket socket = serverSocket.accept();

                InputStreamReader in = new InputStreamReader(socket.getInputStream());
                BufferedReader br = new BufferedReader(in);

                String message = br.readLine();
                String messageParts[] = message.split(",");

                if(messageParts.length == 3){
                    String type = messageParts[0];
                    String ip = messageParts[1];
                    String user = messageParts[2];

                    requestIp = ip;
                    requestName = user;

                    if(type.equals("connect")){
                        isRequestPresent = true;
                        System.out.println("Incoming request from " + user + "@" + ip);
                        System.out.println("Y to accept, N to decline");
                    }

                    if(type.equals("accepted")){
                        isChatActive = true;
                        Chat chatThread = new Chat(user);
                        chatThread.start();
                        chatThread.join();
                    }

                    if(type.equals("rejected")){
                        System.out.println("Request Rejected");
                    }
                }

            }
        }catch(Exception e){}
    }

    public static void sendResponse(char responseChar){
        try{
            Socket socket = new Socket(requestIp, 1234);
            PrintWriter pr = new PrintWriter(socket.getOutputStream());

            String response = "";
            if(responseChar == 'y'){
                isChatActive = true;
                response = "accepted," + Node.IP + "," + Node.username;
                pr.println(response);
                pr.flush();
                Chat chatThread = new Chat(requestName);
                chatThread.start();
                chatThread.join();
            }else{
                response = "rejected," + Node.IP + "," + Node.username;
                pr.println(response);
                pr.flush();
            }
            socket.close();
        }catch(Exception e){}
    }
}

class ConnectRequest extends BaseThread{
    public static Scanner scanner = new Scanner(System.in);

    @Override
    public void run() {
        while(true){
            String str = scanner.nextLine();
            if(isChatActive){
                Chat.sendMessage(str);
            }
            else if(isRequestPresent){
                ConnectListen.sendResponse(str.charAt(0));
                isRequestPresent = false;
            }
            else{
                int n = Integer.parseInt(str);
                String ip = MulticastClient.getNthIP(n);
                requestIp = ip;
                System.out.println("Sending connect request to: " + ip);

                try{
                    Socket socket = new Socket(ip, 1234);
                    PrintWriter pr = new PrintWriter(socket.getOutputStream());

                    pr.println("connect," + Node.IP + "," + Node.username);
                    pr.flush();
                    socket.close();
                }catch(Exception e){}
            }
        }
    }
}

class ChatReceiver extends BaseThread{
    String name;
    ChatReceiver(String nm){
        name = nm;
    }
    @Override
    public void run() {
        try{
            while(true){
                ServerSocket serverSocket = new ServerSocket(12121);
                Socket s = serverSocket.accept();

                InputStreamReader in = new InputStreamReader(s.getInputStream());
                BufferedReader br = new BufferedReader(in);

                System.out.println(name + ": " + br.readLine());
                s.close();
                serverSocket.close();
            }
        }catch(Exception e){}
    }
}

class Chat extends BaseThread{
    String Name;
    Chat(String nm){
        Name = nm;
    }
    @Override
    public void run(){
        isChatActive = true;
        System.out.println("\033[2J\033[HChat Started with " + Name);
        ChatReceiver cr = new ChatReceiver(Name);
        cr.start();
    }

    public static void sendMessage(String msg){
        System.out.println("You: " + msg);
        try{
            Socket s = new Socket(requestIp, 12121);
            PrintWriter pr = new PrintWriter(s.getOutputStream());
            pr.println(msg);
            pr.flush();
            pr.close();
            s.close();
        }catch(Exception e){}
    }
}

public class Node {
    public static String IP;
    public static String username;

    public static ConnectRequest connectRequestThread = new ConnectRequest();

    public static void main(String[] args) {

        String filePath = "chat.config"; // Replace with the actual file path

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            Node.IP = reader.readLine();
            Node.username = reader.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }

        PingThread pingThread = new PingThread();
        pingThread.start();

        ListenThread listenThread = new ListenThread();
        listenThread.start();

        Node.connectRequestThread.start();

        ConnectListen connectListenThread = new ConnectListen();
        connectListenThread.start();

        try{
            // connectRequestThread.join();
            connectListenThread.join();
            pingThread.join();
            listenThread.join();
        }catch(Exception e){
            System.out.println(e.getStackTrace());
        }
    }
}