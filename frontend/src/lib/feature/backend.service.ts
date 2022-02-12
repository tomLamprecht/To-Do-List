import { HttpClient } from "@angular/common/http";
import { Injectable } from "@angular/core";
import { Observable, Subject } from "rxjs";
import { ListModel } from "../data-access/models/listModel";
import { ReminderItemModel } from "../data-access/models/reminderItemModel";

@Injectable ({ providedIn : 'root'})
export class BackendService{
  constructor(private httpClient: HttpClient){}

  ip = "http://127.0.0.1:8080";


  getLists():Observable<ListModel[]>{
    return this.httpClient.get<ListModel[]>(this.ip + "/api/board/lists");
  }

  deleteList(listID){
    this.httpClient.delete(this.ip+"/api/board/lists/"+listID).subscribe( (resp) => {});
  }

  postList(name):Observable<ListModel>{
    return this.httpClient.post<ListModel>(this.ip+"/api/board/lists", {name});
  }

  putList(listId, name){
    this.httpClient.put(this.ip+"/api/board/lists/"+listId, {name} ).subscribe((resp) => {});
  }

  postReminder(listId, title, timestamp, flag):Observable<ReminderItemModel>{
    return this.httpClient.post<ReminderItemModel>(this.ip+"/api/board/lists/" + listId + "/reminders", {title, timestamp, flag});
  }

  deleteReminder(reminderId){
    this.httpClient.delete(this.ip+"/api/board/reminders/"+reminderId).subscribe( (resp) => {});
  }

  putReminder(reminderId, title, timestamp, flag){
    this.httpClient.put(this.ip+"/api/board/reminders/"+reminderId, {title, timestamp, flag}).subscribe( (resp) => {})
  }

  getFlagList():Observable<ListModel>{
    return this.httpClient.get<ListModel>(this.ip+"/api/board/reminders/withFlag");
  }

  getTodayList():Observable<ListModel>{
    const d = new Date();
    let day = (d.getDate().toString().length == 1 ? "0" : "") + d.getDate();

    let date ="'" + d.getFullYear() + "-" + d.getMonth()+1 +"-" + day + "'";
    let resp = new Subject<ListModel>();
    return  this.httpClient.get<ListModel>(this.ip+"/api/board/reminders/withTimestamp/"+date);
  }


}
