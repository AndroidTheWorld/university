package main;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;





public class Windows extends JFrame{
	/**
	 * 
	 */
	private static final long serialVersionUID = -8009028078298506405L;	
	
	public static int screenWidth;
	public static int screenHeight;
	public static SQL sql=null;
	
	private static JPanel panel=null;
	private int userID=0;
	
	public Windows() {
		// TODO �Զ����ɵĹ��캯�����
		Dimension screenSize=Toolkit.getDefaultToolkit().getScreenSize();
		screenWidth=screenSize.width;
		screenHeight=screenSize.height;
		sql=new SQL();
		
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public void loginMenu(double d) {
		this.setSize(200,200);
		this.setTitle("ͨѶ¼��½");
		
		panel=new JPanel();
		panel.setLayout(null);
		this.setContentPane(panel);
		
		JLabel userNameLabel=new JLabel("�û�����");
		userNameLabel.setBounds(20,20,40,12);
		panel.add(userNameLabel);
		
		JTextField userNameField=new JTextField(20);
		userNameField.setBounds(60,20,100,16);
		panel.add(userNameField);
		
		JLabel passLabel=new JLabel("��    �룺");
		passLabel.setBounds(20, 60, 40, 12);
		panel.add(passLabel);
		
		JPasswordField passField=new JPasswordField(20);
		passField.setBounds(60, 60, 100, 16);
		panel.add(passField);
		
		JButton loginButton=new JButton("��½");
		loginButton.setBounds(40,100,40,20);
		loginButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				String username=userNameField.getText();
				String password=new String(passField.getPassword());
				int temp=sql.login(username, password);
				if (temp!=0) {
					log("��½�ɹ�");
					userID=temp;
					mainWindow(0.6);
				}
				else {
					JOptionPane.showMessageDialog(loginButton, "�˻������������");
					passField.setText(null);
				}
			}
		});
		panel.add(loginButton);
		
		JButton registButton=new JButton("ע��");
		registButton.setBounds(100,100,40,20);
		registButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				registerMenu(0.25);
			}
		});
		panel.add(registButton);
		
		this.setLocation((int)((screenWidth-this.getWidth())/2),(int)((screenHeight-this.getHeight())/2));
		this.modifyCompSize(d);
		this.setVisible(true);
	}
	
	public void mainWindow(double d) {
		this.setSize(800,600);
		this.setTitle("ͨѶ¼");
		
		
		panel=new JPanel();
		panel.setLayout(null);
		this.setContentPane(panel);
		
		ContactTable contactTable=new ContactTable(userID,sql);
//		JScrollPane scrollPane=new JScrollPane(contactTable);
//		contactTable.setBounds(10,10,this.getWidth()-15,this.getHeight()-100);
		contactTable.setBounds((int)(this.getWidth()*0.1),(int)(this.getHeight()*0.1),(int)(this.getWidth()*0.8),(int)(this.getHeight()*0.6));
		contactTable.fit();
		panel.add(contactTable);
		
		JButton preButton=new JButton("<");
		preButton.setBounds((int)(this.getWidth()*0.02),(int)(this.getHeight()/2),(int)(this.getWidth()*0.04),(int)(this.getHeight()*0.1));
		preButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				if (!contactTable.preContact()) {
					JOptionPane.showMessageDialog(preButton, "���Ѿ��ǵ�һ����ϵ����");
				}
			}
		});
		panel.add(preButton);
		
		JButton nextButton=new JButton(">");
		nextButton.setBounds((int)(this.getWidth()*0.94),(int)(this.getHeight()/2),(int)(this.getWidth()*0.04),(int)(this.getHeight()*0.1));
		nextButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				if (!contactTable.nextContact()) {
					JOptionPane.showMessageDialog(nextButton, "���Ѿ������һ����ϵ����");
				}
			}
		});
		panel.add(nextButton);
		
		JTextField searchField=new JTextField(20);
		searchField.setBounds((int)(this.getWidth()*0.02),(int)(this.getHeight()*0.72),(int)(this.getWidth()*0.2),(int)(this.getHeight()*0.04));
		panel.add(searchField);
		
		JButton searchButton=new JButton("����");
		searchButton.setBounds((int)(this.getWidth()*0.23),(int)(this.getHeight()*0.72),(int)(this.getWidth()*0.1),(int)(this.getHeight()*0.04));
		searchButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				String text=searchField.getText();
				if (!contactTable.search(text)) {
					JOptionPane.showMessageDialog(searchButton, "δ��ѯ������");
				}
			}
		});
		panel.add(searchButton);
		
		JButton commitEditButton=new JButton("�ύ�޸�");
		commitEditButton.setBounds((int)(this.getWidth()*0.85),(int)(this.getHeight()*0.71),(int)(this.getWidth()*0.1),(int)(this.getHeight()*0.05));
		commitEditButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				if (contactTable.commitEdit(sql)) {
					JOptionPane.showMessageDialog(commitEditButton, "�޸ĳɹ�");
				}
				else {
					JOptionPane.showMessageDialog(commitEditButton, "�޸�ʧ�ܣ������������ݸ�ʽ");
				}
			}
		});
		panel.add(commitEditButton);
		
		
		JButton addButton=new JButton("������ϵ��");
		addButton.setBounds((int)(this.getWidth()*0.85),(int)(this.getHeight()*0.78),(int)(this.getWidth()*0.1),(int)(this.getHeight()*0.05));
		addButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				contactTable.addContact(userID,sql);
			}
		});
		panel.add(addButton);
		
		
		JButton deleteButton=new JButton("ɾ������ϵ��");
		deleteButton.setBounds((int)(this.getWidth()*0.85),(int)(this.getHeight()*0.85),(int)(this.getWidth()*0.1),(int)(this.getHeight()*0.05));
		deleteButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				contactTable.delete(sql);
			}
		});
		panel.add(deleteButton);
		
		JButton logoutButton=new JButton("ע��");
		logoutButton.setBounds((int)(this.getWidth()*0.1),(int)(this.getHeight()*0.85),(int)(this.getWidth()*0.1),(int)(this.getHeight()*0.05));
		logoutButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				loginMenu(0.25);
			}
		});
		panel.add(logoutButton);
		
		this.setLocation((int)((screenWidth-this.getWidth())/2),(int)((screenHeight-this.getHeight())/2));
		this.modifyCompSize(d);
		this.setVisible(true);
		
	}
	
	
	public void registerMenu(double d) {
		this.setSize(200,200);
		this.setTitle("ע��");
		
		panel=new JPanel();
		panel.setLayout(null);
		this.setContentPane(panel);
		
		JLabel userNameLabel=new JLabel("��  ��  ����");
		userNameLabel.setBounds((int)(this.getWidth()*0.1),(int)(this.getHeight()*0.1),(int)(this.getWidth()*0.17),(int)(this.getHeight()*0.07));
		panel.add(userNameLabel);
		
		JTextField usernameField=new JTextField(20);
		usernameField.setBounds((int)(this.getWidth()*0.3),(int)(this.getHeight()*0.1),(int)(this.getWidth()*0.6),(int)(this.getHeight()*0.08));
		panel.add(usernameField);
		
		JLabel passwordLabel1=new JLabel("��        �룺");
		passwordLabel1.setBounds((int)(this.getWidth()*0.1),(int)(this.getHeight()*0.25),(int)(this.getWidth()*0.17),(int)(this.getHeight()*0.07));
		panel.add(passwordLabel1);
		
		JPasswordField passwordField1=new JPasswordField(20);
		passwordField1.setBounds((int)(this.getWidth()*0.3),(int)(this.getHeight()*0.25),(int)(this.getWidth()*0.6),(int)(this.getHeight()*0.08));
		panel.add(passwordField1);
		
		JLabel passwordLabel2=new JLabel("ȷ�����룺");
		passwordLabel2.setBounds((int)(this.getWidth()*0.1),(int)(this.getHeight()*0.4),(int)(this.getWidth()*0.17),(int)(this.getHeight()*0.07));
		panel.add(passwordLabel2);
		
		JPasswordField passwordField2=new JPasswordField(20);
		passwordField2.setBounds((int)(this.getWidth()*0.3),(int)(this.getHeight()*0.4),(int)(this.getWidth()*0.6),(int)(this.getHeight()*0.08));
		panel.add(passwordField2);
		
		JButton registerButton=new JButton("ȷ��ע��");
		registerButton.setBounds((int)(this.getWidth()*0.3),(int)(this.getHeight()*0.55),(int)(this.getWidth()*0.4),(int)(this.getHeight()*0.15));
		registerButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO �Զ����ɵķ������
				String username=usernameField.getText();
				String password1=new String(passwordField1.getPassword());
				String password2=new String(passwordField2.getPassword());
				
				if (sql.queryUser(username)) {
					JOptionPane.showMessageDialog(registerButton, "��Ǹ�����û��Ѵ��ڣ��������Ը��û���ע��");
					usernameField.setText(null);
				}else {
					if (password1.equals(password2)) {
						if (sql.register(username,password1)) {
							JOptionPane.showMessageDialog(registerButton, "ע��ɹ�");
							loginMenu(0.25);
						}else {
							JOptionPane.showMessageDialog(registerButton, "ע��ʧ��");
						}
					}else {
						JOptionPane.showMessageDialog(registerButton, "������������벻һ��");
						passwordField1.setText(null);
						passwordField2.setText(null);
					}
				}
			}
		});
		panel.add(registerButton);
		
		this.setLocation((int)((screenWidth-this.getWidth())/2),(int)((screenHeight-this.getHeight())/2));
		this.modifyCompSize(d);
		this.setVisible(true);
	}
	
	public void modifyCompSize(double d) {
		
		int fraWidth=this.getWidth();
		int fraHeight=this.getHeight();
		this.setSize((int)(screenWidth*d),(int)(screenHeight*d));
		double proportionW=screenWidth*d/fraWidth;
		double proportionH=screenHeight*d/fraHeight;
		
		try {
			Component[] components=this.getRootPane().getContentPane().getComponents();
			for(Component co:components) {
				double locX=co.getX()*proportionW;
				double locY=co.getY()*proportionH;
				double width=co.getWidth()*proportionW;
				double height=co.getHeight()*proportionH;
				co.setLocation((int)locX, (int)locY);
				co.setSize((int)width,(int)height);
				int size=(int)(co.getFont().getSize()*proportionH);
				Font font=new Font(co.getFont().getFontName(),co.getFont().getStyle(),size);
				co.setFont(font);
			}
		} catch (Exception e) {
			// TODO: handle exception
			log("�޷�����Ӧ��Ļ�ߴ�");
		}
	}
	
	public static void log(String str) {
		System.out.println("[WINDOWS_LOG]:"+str);
	}
}

