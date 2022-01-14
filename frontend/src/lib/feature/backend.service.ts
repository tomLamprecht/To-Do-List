import { HttpClient } from "@angular/common/http";
import { Injectable } from "@angular/core";
import { Subject } from "rxjs";
import { ListModel } from "../data-access/models/listModel";
import { ReminderItemModel } from "../data-access/models/reminderItemModel";

@Injectable ({ providedIn : 'root'})
export class BackendService{
  constructor(private httpClient: HttpClient){}

  ip = "http://127.0.0.1:8080";


  getLists():Subject<ListModel[]>{
    let resp = new Subject<ListModel[]>();
    this.httpClient.get(this.ip + "/api/board/lists").subscribe( (response : any) => {resp.next(response);} );
    return resp;
  }

  deleteList(listID){
    this.httpClient.delete(this.ip+"/api/board/lists/"+listID).subscribe( (resp) => {});
  }

  postList(name, position):Subject<ListModel>{
    let resp = new Subject<ListModel>();
    this.httpClient.post(this.ip+"/api/board/lists", {name, position}).subscribe( (response : any) => {resp.next(response)} );
    return resp;
  }

  putList(listId, name, position){
    this.httpClient.put(this.ip+"/api/board/lists/"+listId, {name, position} ).subscribe((resp) => {});
  }

  postReminder(listId, title , position, timestamp, flag):Subject<ReminderItemModel>{
    let resp = new Subject<ReminderItemModel>();
    this.httpClient.post(this.ip+"/api/board/lists/" + listId + "/reminders", {title, position, timestamp, flag}).subscribe( (response : any) => {resp.next(response)});
    return resp;
  }

  deleteReminder(reminderId){
    this.httpClient.delete(this.ip+"/api/board/reminders/"+reminderId).subscribe( (resp) => {});
  }

  putReminder(reminderId, title , position, timestamp, flag){
    this.httpClient.put(this.ip+"/api/board/reminders/"+reminderId, {title, position, timestamp, flag}).subscribe( (resp) => {})
  }

  getFlagList(){
    let resp = new Subject<ListModel>();
    this.httpClient.get(this.ip+"/api/board/reminders/withFlag").subscribe( (response : any) => {resp.next(response)} );
    return resp;
  }

  getTodayList(){
    const d = new Date();
    let day = (d.getDate().toString().length == 1 ? "0" : "") + d.getDate();

    let date ="'" + d.getFullYear() + "-" + d.getMonth()+1 +"-" + day + "'";
    let resp = new Subject<ListModel>();
    this.httpClient.get(this.ip+"/api/board/reminders/withTimestamp/"+date).subscribe( (response : any) => {resp.next(response)} );
    return resp;
  }


}
