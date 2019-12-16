package main;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import java.util.Vector;



public class SQL {
	public static final String DRIVER="com.mysql.cj.jdbc.Driver";
	public static final String URL="jdbc:mysql://localhost:3306/AddressBookSYS?&serverTimezone=UTC";
	public static final String USER="root";
	public static final String PASS="123456";
	
	public static String userTable=null;
    private static Connection conn=null;
    private static PreparedStatement pstmt=null;
	
    public SQL() {
		// TODO �Զ����ɵĹ��캯�����
    	try {
			Class.forName(DRIVER);
			conn=DriverManager.getConnection(URL,USER,PASS);
			log("���ݿ����ӳɹ�");
		} catch (ClassNotFoundException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("װ��MySQL JDBC����ʧ��");
			return;
		} catch ( SQLException e) {
			// TODO: handle exception
    		e.printStackTrace();
    		log("�޷����������ݿ�����");
    		return;
		}
	}
    
    
    public int login(String username,String password) {
    	String sql="select id from user where username=? and password=?";
    	try {
			pstmt=conn.prepareStatement(sql);
	    	pstmt.setString(1, username);
	    	pstmt.setString(2, password);
	    	log(pstmt.toString());
	    	ResultSet res=pstmt.executeQuery();
	    	while (res.next()) {
	    		return res.getInt(1);
	    	}
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("�û���ѯʧ��");
		}  	
    	return 0;
    }
    
    
    public Vector<uEtableModel> tableModelInit(int userid) {
    	Vector<uEtableModel> dtms=new Vector<uEtableModel>();
    	int i=1;
    	
    	String sql="select id,name,sextype,birth,phone1,phone2,telephone,address from contacts where belongto=?";
    	try {
			pstmt=conn.prepareStatement(sql);
			pstmt.setInt(1, userid);
			ResultSet res=pstmt.executeQuery();
			while (res.next()) {
				uEtableModel dtm=new uEtableModel(1);
				dtm.setColumnCount(2);
				dtm.ID=res.getInt("id");
				
				Vector<Object> row=new Vector<Object>();
				row.add("������"); row.add(res.getString("name"));
				dtm.addRow(row);
				
				row=new Vector<Object>();
				row.add("�Ա�"); row.add(res.getString("sextype"));
				dtm.addRow(row);
				
				row=new Vector<Object>();
				row.add("���գ�"); row.add(res.getString("birth"));
				dtm.addRow(row);
				
				row=new Vector<Object>();
				row.add("�ֻ�1��"); row.add(res.getString("phone1"));
				dtm.addRow(row);
				
				row=new Vector<Object>();
				row.add("�ֻ�2��"); row.add(res.getString("phone2"));
				dtm.addRow(row);
				
				row=new Vector<Object>();
				row.add("�绰��"); row.add(res.getString("telephone"));
				dtm.addRow(row);
				
				row=new Vector<Object>();
				row.add("��ͥסַ��"); row.add(res.getString("address"));
				dtm.addRow(row);
				log("�ѻ�ȡ����"+i);
				dtms.add(dtm);
				i=i+1;
			}
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("�޷���ʼ���������");
		}
    	return dtms;
    }
    
    
    public boolean insert(int ID,String name,String sextype,String birth,String phone1,String phone2,String telephone,String address) {
    	String sql="insert into contacts (name,sextype,birth,phone1,phone2,telephone,address,belongto) values (?,?,?,?,?,?,?,?)";
    	try {
			pstmt=conn.prepareStatement(sql);
			
			pstmt.setString(1, name);
			if (sextype.equals("")) pstmt.setString(2, "δ֪");
			else pstmt.setString(2, sextype);
			
			if (birth.equals("")) pstmt.setNull(3,Types.DATE);
			else pstmt.setString(3, birth);
			
			if (phone1.equals("")) pstmt.setNull(4, Types.VARCHAR);
			else pstmt.setString(4, phone1);
			
			if (phone2.equals("")) pstmt.setNull(5, Types.VARCHAR);
			else pstmt.setString(5, phone2);
			
			if (telephone.equals("")) pstmt.setNull(6, Types.VARCHAR);
			else pstmt.setString(6, telephone);
			
			if (address.equals("")) pstmt.setNull(7, Types.VARCHAR);
			else pstmt.setString(7, address);
			pstmt.setInt(8, ID);
			
			if (pstmt.executeUpdate()==1) return true;
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("��������ʧ��");
		}
    	return false;
    }
    
    
    public boolean delete(int id) {
    	String sql="delete from contacts where id=?";
    	
    	log(String.valueOf(id));
    	try {
			pstmt=conn.prepareStatement(sql);
			pstmt.setInt(1, id);
			if (pstmt.executeUpdate()==1) return true;
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("δ�ܳɹ�ɾ������");
		}
    	return false;
    }
    
    public boolean update(int ID,String name,String sextype,String birth,String phone1,String phone2,String telephone,String address) {
		String sql="update contacts set name=?,sextype=?,birth=?,phone1=?,phone2=?,telephone=?,address=? where id=?";
		try {
			pstmt=conn.prepareStatement(sql);
			pstmt.setString(1, name);
			pstmt.setString(2, sextype);
			pstmt.setString(3, birth);
			pstmt.setString(4, phone1);
			pstmt.setString(5, phone2);
			pstmt.setString(6, telephone);
			pstmt.setString(7, address);
			pstmt.setInt(8, ID);
			
			if (pstmt.executeUpdate()==1) return true;
			
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("�޷���������");
		}
		return false;
	}
    
    public boolean queryUser(String username) {
    	String sql="select count(*) from user where username=?";
    	try {
			pstmt=conn.prepareStatement(sql);
			pstmt.setString(1, username);
			ResultSet res=pstmt.executeQuery();
			while(res.next()) {
				if (res.getInt("count(*)")==1) return true; 
			}
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("�޷���ѯ�û��Ƿ����");
		}
    	return false;
    }
    
    public boolean register(String username,String password) {
    	String sql="insert into user (username,password) values (?,?)";
    	try {
			pstmt=conn.prepareStatement(sql);
			pstmt.setString(1, username);
			pstmt.setString(2, password);
			pstmt.executeUpdate();
			return true;
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("�޷���������û�");
		}
    	return false;
    }
    
    public void resetContact() {
		String sql="truncate table contacts";
		
		try {
			pstmt=conn.prepareStatement(sql);
			pstmt.execute();
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("�޷��������ñ��");
		}
	}
    
    public int GetID() {
		// TODO �Զ����ɵķ������
		String sql="select max(id) from contacts";
		try {
			pstmt=conn.prepareStatement(sql);
			ResultSet res=pstmt.executeQuery();
			while (res.next()) {
				return res.getInt(1);
			}
		} catch (SQLException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
			log("�޷�������ȡID");
		}
		
		return 0;
	}
    
    @SuppressWarnings("deprecation")
	@Override
    protected void finalize() throws Throwable {
    	// TODO �Զ����ɵķ������
    	super.finalize();
    	if (pstmt!=null) pstmt.close();
    	conn.close();
    }
    
	public  void init() {
		
	}
	
	
	
	public static void log(String str) {
		System.out.println("[SQL_LOG]:"+str);
	}


	

}
