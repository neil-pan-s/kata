package demo.org.ichanging.intent;

import java.io.Serializable;

public class Person implements Serializable{
	private Integer id;
	private String name;
	private String pwd;
	private String gender;

	public Person(String name, String passwd, String gender) {
		this.name = name;
		this.pwd = passwd;
		this.gender = gender;
	}

	public Integer getId() {
		return id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getPwd() {
		return pwd;
	}

	public void setPwd(String passwd) {
		this.pwd = passwd;
	}

	public String getGender() {
		return gender;
	}

	public void setGender(String gender) {
		this.gender = gender;
	}
}
