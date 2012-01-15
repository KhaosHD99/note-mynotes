package org.apache.musicplf.domain;

public class Basictable 
{
    private Integer id;
    private String name;
    private String desc;
    private String remark;

    public Integer getId() 
    {
        return id;
    }

    public void setId(Integer id) 
    {
        this.id = id;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name) 
    {
        this.name = name;
    }

    public String getDesc() 
    {
        return desc;
    }

    public void setDesc(String desc) 
    {
        this.desc = desc;
    }

    public String getRemark() 
    {
        return remark;
    }

    public void setRemark(String remark)
    {
        this.remark = remark;
    }
}