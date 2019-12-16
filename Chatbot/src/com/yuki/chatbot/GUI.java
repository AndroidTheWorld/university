package com.yuki.chatbot;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.LayoutManager;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.net.URL;

import javax.sound.sampled.AudioFileFormat;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.SourceDataLine;
import javax.sound.sampled.TargetDataLine;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class GUI extends JFrame implements MouseListener{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	//���ðٶ�API
	public static final String APP_ID="10516591";
	public static final String API_KEY="GRGH0HfpUjwvE1tnZ0HdEtyb";
	public static final String SECRET_KEY="1e4d107c7a621594a2601d1635fcbd25";
	private static BaiduAPI baidu = null;
	
	private JButton button_recoad=null;
	private JPanel panel=null;
	
	//����¼����ʽ
	private static final AudioFormat af =new AudioFormat(AudioFormat.Encoding.PCM_SIGNED,16000f, 16, 1, 2, 16000f,true);
	//����Ŀ��������,���Դ��ж�ȡ��Ƶ����,�� TargetDataLine �ӿ��ṩ��Ŀ�������еĻ�������ȡ���������ݵķ�����
	private static TargetDataLine td = null;
	//����Դ������,Դ�������ǿ���д�����ݵ������С����䵱���Ƶ����Դ��Ӧ�ó�����Ƶ�ֽ�д��Դ�����У������ɴ����ֽڻ��岢�����Ǵ��ݸ���Ƶ����
	private static SourceDataLine sd = null;
	//�����ֽ��������������
	private ByteArrayInputStream bais = null;
	private ByteArrayOutputStream baos = null;
	//������Ƶ������
	private static AudioInputStream ais = null;
	//����ֹͣ¼���ı�־��������¼���̵߳�����
	Boolean stopflag = false;
	private  URL url0=getClass().getResource("/micro0.png");
	private  URL url1=getClass().getResource("/micro1.png");
	private  Icon micro0 = new ImageIcon(url0);
	private  Icon micro1 = new ImageIcon(url1);

	
	public GUI(String title) throws Exception{
		super("Chat Robot");
		this.setSize(512, 512);
		this.setDefaultCloseOperation(this.EXIT_ON_CLOSE);
		this.setLayout(new BorderLayout(10, 10));
		
		panel = new JPanel();
		this.add(panel);
		panel.setLayout(new BorderLayout(10,10));
		
		button_recoad = new JButton("");
		button_recoad.setSize(256, 256);
		button_recoad.setIcon(micro0);
		//button_recoad.setBounds(100, 50, 100, 50);
		button_recoad.addMouseListener(this);
		panel.add(button_recoad,BorderLayout.CENTER);
		
		this.setVisible(true);
		
		baidu=new BaiduAPI(APP_ID, API_KEY, SECRET_KEY);
	}
	
	public void mouseClicked(MouseEvent e) {
//		System.out.println("clicked");
	}
	
	public void mousePressed(MouseEvent e) {
		if (e.getSource().equals(button_recoad)) {
//			System.out.println("pressed");
			button_recoad.setIcon(micro1);;
			capture();
		}
	}
	
	public void mouseReleased(MouseEvent e) {
		if (e.getSource().equals(button_recoad)) {
//			System.out.println("pressed");
			stopflag=true;
			button_recoad.setIcon(micro0);
			save();
			baidu.voice2words();
			
		}
	}
	
	public void mouseEntered(MouseEvent e) {
		
	}
	
	public void mouseExited(MouseEvent e) {
		
	}

	public void capture() {
		try {
			try {
				td.close();
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
			DataLine.Info info = new DataLine.Info(TargetDataLine.class, af);
			td = (TargetDataLine)(AudioSystem.getLine(info));
			
			td.open(af);
			
			td.start();
			
			Record record = new Record();
			Thread t1 = new Thread(record);
			t1.start();
			
			
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			return;
		}
	}

	
	public void save() {
		 
        byte audioData[] = baos.toByteArray();
        bais = new ByteArrayInputStream(audioData);
        ais = new AudioInputStream(bais,af, audioData.length / af.getFrameSize());
        //�������ձ�����ļ���
        File file = null;
        //д���ļ�
        try {	
        	//�Ե�ǰ��ʱ������¼��������
        	//��¼�����ļ���ŵ�F���������ļ�����
        	File filePath = new File("./temp");
        	if(!filePath.exists())
        	{//����ļ������ڣ��򴴽���Ŀ¼
        		filePath.mkdir();
        	}
        	file = new File(filePath.getPath()+"/record.mp3");      
            AudioSystem.write(ais, AudioFileFormat.Type.WAVE, file);
        } catch (Exception e) {
            e.printStackTrace();
        }finally{
        	//�ر���
        	try {
        		
        		if(bais != null)
        		{
        			bais.close();
        		} 
        		if(ais != null)
        		{
        			ais.close();		
        		}
			} catch (Exception e) {
				e.printStackTrace();
			}   	
        }

	}

	
	class Record implements Runnable{
		//������¼�����ֽ�����,��Ϊ������
		byte bts[] = new byte[10000];
		//���ֽ������װ��������մ��뵽baos��
		//��дrun����
		public void run() {	
			baos = new ByteArrayOutputStream();		
			try {
				System.out.println("Recoding...");
				stopflag = false;
				while(stopflag != true)
				{
					//��ֹͣ¼��û����ʱ�����߳�һֱִ��	
					//�������е����뻺������ȡ��Ƶ���ݡ�
					//Ҫ��ȡbts.length���ȵ��ֽ�,cnt ��ʵ�ʶ�ȡ���ֽ���
					int cnt = td.read(bts, 0, bts.length);
					if(cnt > 0)
					{
						baos.write(bts, 0, cnt);
					}
				}
			} catch (Exception e) {
				e.printStackTrace();
			}finally{
				try {
					//�رմ򿪵��ֽ�������
					if(baos != null)
					{
						baos.close();
					}	
				} catch (IOException e) {
					e.printStackTrace();
				}finally{
					td.drain();
					td.close();
				}
			}
		}
	}
	
}