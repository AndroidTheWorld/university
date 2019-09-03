package cc.yuukisama.Entity;

import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;

import cc.yuukisama.JFrame.GameJFrame;

public class GoldCoin extends UnityBase {

	public int type=2;
	public GoldCoin(int t) {
		// TODO �Զ����ɵĹ��캯�����
		WIDTH=(int)(GameJFrame.WIDTH*0.04);
		HEIGHT=(int)(GameJFrame.HEIGHT*0.04);
		x=(int)(random.nextInt(GameJFrame.WIDTH));
		y=(int)(GameJFrame.HEIGHT/2-random.nextInt((int)(GameJFrame.HEIGHT*0.5)));
		imageNum=2;
		index=0;
		
		time=0;
		interval=5;
		
		type=t;
		image=new Image[imageNum];
		for(int i=0;i<imageNum;i++)
			image[i]=new ImageIcon("resource/image/"+type+(i+1)+".png").getImage();
	}
	public GoldCoin() {
		// TODO �Զ����ɵĹ��캯�����
		WIDTH=(int)(GameJFrame.WIDTH*0.04);
		HEIGHT=(int)(GameJFrame.HEIGHT*0.04);
		x=(int)(GameJFrame.WIDTH+random.nextInt(GameJFrame.WIDTH));
		y=(int)(GameJFrame.HEIGHT/2-random.nextInt((int)(GameJFrame.HEIGHT*0.5)));
		imageNum=2;
		index=0;
		
		time=0;
		interval=5;
		
		type=random.nextInt(2)+2;
		image=new Image[imageNum];
		for(int i=0;i<imageNum;i++)
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
