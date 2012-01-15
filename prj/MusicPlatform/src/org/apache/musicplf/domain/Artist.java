package org.apache.musicplf.domain;

public class Artist {
    
    private Integer id;
    private String artName;
    private String signedcompany;
    
    public Integer getId()
    {
        return id;
    }
    public void setId(Integer id) 
    {
        this.id = id;
    }
    
    public String getArtName() 
    {
        return artName;
    }

    public void setArtName(String artName) 
    {
        this.artName = artName;
    }

    public String getSignedcompany() 
    {
        return signedcompany;
    }

    public void setSignedcompany(String signedcompany)
    {
        this.signedcompany = signedcompany;
    }
}