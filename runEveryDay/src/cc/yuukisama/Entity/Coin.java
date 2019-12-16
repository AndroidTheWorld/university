package cc.yuukisama.Entity;

import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;

import cc.yuukisama.JFrame.GameJFrame;

public class Coin extends UnityBase {
	public int type=2;
	
	public Coin(int startY,int t) {
		// TODO �Զ����ɵĹ��캯�����
		WIDTH=(int)(GameJFrame.WIDTH*0.04);
		HEIGHT=(int)(GameJFrame.HEIGHT*0.04);
		x=(int)(GameJFrame.WIDTH*0.2);
		y=startY;
		imageNum=2;
		index=0;
		
		time=0;
		interval=5;
		
		type=t;
		image=new Image[imageNum];
		for (int i=0;i<imageNum;i++) 
			image[i]=new ImageIcon("resource/image/"+type+(i+1)+".png").getImage();
	}
	
	public Coin(Coin pre) {
		// TODO �Զ����ɵĹ��캯�����
		WIDTH=(int)(GameJFrame.WIDTH*0.04);
		HEIGHT=(int)(GameJFrame.HEIGHT*0.04);
		x=(int)(pre.x+WIDTH+GameJFrame.WIDTH*0.005);
		y=pre.y;
		imageNum=2;
		index=0;
		
		time=0;
		interval=5;
		
		type=pre.type;
		image=new Image[imageNum];
		for (int i=0;i<imageNum;i++) 
			image[i]=new ImageIcon("resource/image/"+type+(i+1)+".png").getImage();
	}

	@Override
	public void paint(Graphics g) {
		// TODO �Զ����ɵķ������
		if (isGo()) {
			step();
			g.drawImage(image[index], x--, y, WIDTH, HEIGHT, null);
		}
		else{
			g.drawImage(image[index], x--, y, WIDTH, HEIGHT, null);
		}
	}

}
