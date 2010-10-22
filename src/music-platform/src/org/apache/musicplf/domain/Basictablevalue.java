package org.apache.musicplf.domain;

public class Basictablevalue 
{
    private Integer id;
    private String value;
    private String desc;
    private Integer basictableId;

    public Integer getId() 
    {
        return id;
    }

    public void setId(Integer id) 
    {
        this.id = id;
    }

    public String getValue() 
    {
        return value;
    }

    public void setValue(String value)
    {
        this.value = value;
    }

    public String getDesc() 
    {
        return desc;
    }

    public void setDesc(String desc) 
    {
        this.desc = desc;
    }

    public Integer getBasictableId() 
    {
        return basictableId;
    }

    public void setBasictableId(Integer basictableId) 
    {
        this.basictableId = basictableId;
    }
}