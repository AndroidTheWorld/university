package main;

import java.util.Vector;

import javax.swing.JOptionPane;
import javax.swing.JTable;



public class ContactTable extends JTable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1313814071826449680L;
	public static Vector<uEtableModel> dtms=null;
	private static int i=0;
	
	public ContactTable(int userid,SQL sql) {
		// TODO �Զ����ɵĹ��캯�����
		this.getTableHeader().setVisible(false);
		i=0;
		dtms=sql.tableModelInit(userid);
		
		if (dtms.size()<1) this.setModel(emptyModel());
		else this.setModel(dtms.firstElement());
//		this.fit();
	}
	
	
	public uEtableModel emptyModel() {
		uEtableModel contact=new uEtableModel(i);
		contact.addRow(new Object[] {"������",null});
		contact.addRow(new Object[] {"�Ա�",null});
		contact.addRow(new Object[] {"���գ�",null});
		contact.addRow(new Object[] {"�ֻ�1��",null});
		contact.addRow(new Object[] {"�ֻ�2��",null});
		contact.addRow(new Object[] {"�绰��",null});
		contact.addRow(new Object[] {"��ͥסַ��",null});
		return contact;
	}
	
	public void fit() {
		this.getColumnModel().getColumn(0).setMaxWidth((int)(this.getWidth()*0.2));
		this.setRowHeight((int)(this.getHeight()/7));
	}
	
	
	public static int getI() {
		return i;
	}
	
	
	public void addContact(int userID,SQL sql) {
		String name=JOptionPane.showInputDialog(this,"��������ϵ��������");
		while (name.equals("") || name==null) {
			if (name==null) return;
			name=JOptionPane.showInputDialog(this,"��������ϵ��������");
		}
		String sextype=JOptionPane.showInputDialog(this,"��������ϵ���Ա��У�Ů��δ֪����");
		String birth=JOptionPane.showInputDialog(this,"��������ϵ�����գ�YYYY-MM-DD����");
		String phone1=JOptionPane.showInputDialog(this,"��������ϵ���ֻ�1��");
		String phone2=JOptionPane.showInputDialog(this,"��������ϵ���ֻ�2��");
		String telephone=JOptionPane.showInputDialog(this,"��������ϵ�˵绰��");
		String address=JOptionPane.showInputDialog(this,"��������ϵ�˼�ͥסַ��");
		
		if (sql.insert(userID,name,sextype,birth,phone1,phone2,telephone,address)) {
			
			uEtableModel contact=new uEtableModel(i);
			if (name=="NULL") name=null;
			contact.addRow(new Object[] {"������",name});
			
			contact.addRow(new Object[] {"�Ա�",sextype});
			
			if (birth=="NULL") birth=null;
			contact.addRow(new Object[] {"���գ�",birth});
			
			if (phone1=="NULL") phone1=null;
			contact.addRow(new Object[] {"�ֻ�1��",phone1});
			
			if (phone2=="NULL") phone2=null;
			contact.addRow(new Object[] {"�ֻ�2��",phone2});
			
			if (telephone=="NULL") telephone=null;
			contact.addRow(new Object[] {"�绰��",telephone});
			
			if (address=="NULL") address=null;
			contact.addRow(new Object[] {"��ͥסַ��",address});
			
			contact.ID=sql.GetID();
			if (dtms.size()<1) i=0;
			else i=i+1;
			dtms.add(contact);
			
			this.setModel(dtms.get(i));
			this.fit();
			JOptionPane.showMessageDialog(this, "����ɹ�");
			return;
		};
		JOptionPane.showMessageDialog(this, "����ʧ��");
		return;
		
	}
	
	
	public void delete(SQL sql) {
		int id=dtms.get(i).ID;
		if (sql.delete(id)) {
			dtms.remove(i);
			if (dtms.size()<1) {
				i=0;
				sql.resetContact();
				this.setModel(emptyModel());
				this.fit();
				return;
			}
			i=i%dtms.size();
			this.setModel(dtms.get(i));
			this.fit();
			JOptionPane.showMessageDialog(this, "ɾ���ɹ�");
			return;
		}
		JOptionPane.showMessageDialog(this, "ɾ��ʧ��");
		return;
	}
	
	public boolean search(String str) {
		boolean isFind=false;
		for (uEtableModel x:dtms) {
			int rowNum=x.getRowCount();
			for (int i=0;i<rowNum;i++) {
				String data="";
				try {
					data=x.getValueAt(i, 1).toString();
				} catch (NullPointerException e) {
					// TODO: handle exception
				}
				
				if (data.indexOf(str)!=-1) {
					isFind=true; 
					break;
				}
			}
			this.setModel(x);
			fit();
			if (isFind) return isFind;
		}
		return isFind;
	}
	
	public boolean commitEdit(SQL sql) {
		int id=dtms.get(i).ID;
		String name=this.getValueAt(0, 1).toString();
		String sextype=this.getValueAt(1, 1).toString();
		String birth="NULL";
		if (this.getValueAt(2, 1)!=null) birth=this.getValueAt(2, 1).toString();
		String phone1="NULL";
		if (this.getValueAt(3, 1)!=null) phone1=this.getValueAt(3, 1).toString();
		String phone2="NULL";
		if (this.getValueAt(4, 1)!=null) phone2=this.getValueAt(4, 1).toString();
		String telephone="NULL";
		if (this.getValueAt(5, 1)!=null) telephone=this.getValueAt(5, 1).toString();
		String address="NULL";
		if (this.getValueAt(6, 1)!=null) address=this.getValueAt(6, 1).toString();
		
		return sql.update(id,name,sextype,birth,phone1,phone2,telephone,address);
	}
	
	@SuppressWarnings("unused")
	private void log(String string) {
		// TODO �Զ����ɵķ������
		System.out.println("[TABLE_LOG]:"+string);
	}

	public boolean preContact() {
		if (i-1>=0) {
			i=i-1;
			this.setModel(dtms.get(i));
			fit();
			return true;
		}
		return false;
	}
	
	public boolean nextContact() {
		if (i+1<dtms.size()) {
			i=i+1;
			this.setModel(dtms.get(i));
			fit();
			return true;
		}
		return false;
	}

}
