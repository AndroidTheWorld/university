package sj.db.dao;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import sj.db.bean.Administrator;
import sj.db.bean.Record;
import sj.db.util.GenerateCode;
import sj.db.util.JDBCUtils;

public class AdminDao {
	//��½�ж�
	public boolean judegLogin(Administrator admin) {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;
		try {
			conn = JDBCUtils.getConnection();
			stmt = conn.createStatement();
			String sql = "select Admin_name,Admin_pwd from Administrator where Admin_name ='"
					+ admin.getAdmin_name()
					+ "'and Admin_pwd ='"
					+ admin.getAdmin_pwd() 
					+ "'";
			rs = stmt.executeQuery(sql);
			if(rs.next()) {
				return true;
			} else {
				return false;
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			JDBCUtils.release(rs, stmt, conn);
		}
		return false;
	}
	//��ȡ�û��б�
	public List<Administrator> getAdmin(){
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;
		List<Administrator>adminList = new ArrayList<Administrator>();
			try {
				conn = JDBCUtils.getConnection();
				stmt = conn.createStatement();
				String sql = "select * from Administrator";
				rs = stmt.executeQuery(sql);
				while(rs.next()) {
					Administrator admin = new Administrator();
					admin.setAdmin_id(rs.getInt("Admin_id"));
					admin.setAdmin_name(rs.getString("Admin_name"));
					admin.setAdmin_pwd(rs.getString("Admin_pwd"));
					admin.setAdmin_new_code(rs.getString("Admin_code"));
					adminList.add(admin);
				}
			} catch (Exception e) {
				e.printStackTrace();
			} finally {
				JDBCUtils.release(rs, stmt, conn);
			}
			return null;
	}
	//����id��ȡ�û�
	//�����û�
	public boolean insert(Administrator admin) {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs =null;
		try {
			conn = JDBCUtils.getConnection();
			stmt = conn.createStatement();
			//��ѯ���û������������Ƿ������ݿ���
			String old_code = admin.getAdmin_old_code();
			String sql1 = "select Admin_code from Administrator "
					+ "where Admin_code ='"+ old_code+"'";
			rs = stmt.executeQuery(sql1);
			if(rs.next()) {//���������
				//�������һ�����������ע����˺�
				int code = GenerateCode.code();
				String sql2 = "insert into Administrator(Admin_id,Admin_name,Admin_pwd,Admin_code)"
						+ "values(" + null 
						+ ",'" 
						+ admin.getAdmin_name() 
						+ "','" 
						+ admin.getAdmin_pwd() 
						+ "','" 
						+ code 
						+ "')"; 
				int num = stmt.executeUpdate(sql2);
				if(num > 0) {
					return true;//ע��ɹ�
				}
				return false;//ע��ʧ��
			} else {//�����벻����
				return false;
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			JDBCUtils.release(rs, stmt, conn);
		}
		return false;
	}
	//ɾ���û�
	//�޸��û�
	public boolean update(Administrator admin) {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs =null;
		try {
			conn = JDBCUtils.getConnection();
			stmt = conn.createStatement();
			String sql = "update administrator set Admin_id='"+ null +"',"
					+ "Admin_name='"+ admin.getAdmin_name() +"',"
							+ "Admin_pwd='"+ admin.getAdmin_pwd();//�����벻���޸�
			int num = stmt.executeUpdate(sql);
			if(num > 0) {
				return true;
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			JDBCUtils.release(rs, stmt, conn);
		}
		return false;
	}
}
